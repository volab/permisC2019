/**
 @file robot.cpp
 @author J.SORANZO
 @date 02/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief fichier d'implémentation de la classe CRobotJunior
*/

#include "robot.h"
extern RF24 radio; //devrait faire partie de la classe a terme !

void CRobotJunior::init( unsigned long tempsCycle ){
    _initLeds();
    _initSensors();
    _initBuzzer();
    _initMotors();
    _liner.begin(
          LINESENSOR_GAUCHE_EXTERNE_PIN
        , LINESENSOR_GAUCHE_MILIEUX_PIN
        , LINESENSOR_GAUCHE_INTERNE_PIN
        , LINESENSOR_DROITE_INTERNE_PIN 
        , LINESENSOR_DROITE_MILIEUX_PIN
        , LINESENSOR_DROITE_EXTERNE_PIN    
    );

    
    _prevMillis = millis();
    
    _tempsCycle = tempsCycle;
    pinMode( TIMECYCLEMESU_PIN, OUTPUT );
    digitalWrite( TIMECYCLEMESU_PIN, LOW );
    _inRun = false;
    _lignePerdue = false;
    _cptPerteLigne = 0;
    _etat = FOLLOWLIGNE;
    _detectTagOn = false;
    _etatRobot = FOLLOWLIGNE;
}


void CRobotJunior::update(){
    _updateLeds();
    _updatesSensors();
    _liner.forceUpdate();
    _buz.update(); 
    if ( millis() - _prevMillis > _tempsCycle ){
        digitalWrite( TIMECYCLEMESU_PIN , HIGH ); //to mesure cycle time
        _prevMillis = millis();
        byte capteurLigneDroite = _liner.getValueDroite();
        byte capteurLigneGauche = _liner.getValueGauche();
        switch ( _etatRobot ){
            case FOLLOWLIGNE:
                _followTheLigne( capteurLigneGauche, capteurLigneDroite );
                if ( _lignePerdue ){
                   _buz.ligneLostSound();
                  _etatRobot = LIGNELOST;  
                } 
                break;
            case LIGNELOST:
                _motG.stop();
                _motD.stop(); 
                _cptPause = 300;
                _etatRobot = PAUSE;
                break;
            case PAUSE:
                if ( !_cptPause-- ){
                    _cptRecul = CPT_LIG_LOST_MAX+CPT_LIG_LOST_MAX/2;
                    _etatRobot = RECULE;
                } 
                break;
            case RECULE:
                if ( _cptRecul != 0){
                    _motD.recule( _vitesseDeBase );
                    _motG.recule( _vitesseDeBase );
                    _cptRecul--;
                } else {
                    _cptTour = 0;
                    _vitesGaucheRetrive = 0;
                    _etatRobot = RETRIVELIGN;
                }
                break;
            case RETRIVELIGN:
                if ( _retriveLigne() ){
                    _motG.stop();
                    _motD.stop(); 
                    _etatRobot = END;
                }
                break;
            case END:
                for(;;){
                    _allumeDroiteGauche();
                    delay(200);
                    _eteindLed();
                    delay(200);
                }  
                break;
        }        
        
        if ( capteurLigneDroite == 7 && capteurLigneGauche == 7 ) return; //pour arrêter les acquisitions

        // char trame[ TAILLE_TRAME + 1 ];
        _bat = (analogRead(A0)*5.0/1024.0)/.586;
        _batEnt = int( _bat );
        _batDec = int( (_bat - _batEnt) *10.0 );
        unsigned long temps = millis();
        char c = '*';
        int tagDist = _usGauche.getDistance();
        
        if ( tagDist > 0 && tagDist < 20 ){
            if ( _detectTagOn == 0 ){
                c = 'T'; //T for TAG unique char to find in the file it is more easy
                _ledCapteurGauche.onFlash(300);
                _detectTagOn = 100; //100 cycles soit 1000ms   avec un cycle de 10ms  
                // soit environ 40cm à 0.47 m/s VBAT 7V  Vconsigne 110                 
            }
        }
        if (_etatRobot == RECULE) c='R';
        if (_etatRobot == RETRIVELIGN) c='C';
        if ( _detectTagOn != 0) _detectTagOn--;
        sprintf( _trame, "%06lu,%d,%d,%d.%d,%c"
                    , temps
                    , capteurLigneGauche
                    , capteurLigneDroite
                    , _batEnt
                    , _batDec
                    , c );
        radio.write( _trame, TAILLE_TRAME, 0 ); //noack - enableDynamicAck appelé dans le setup
        
        digitalWrite( TIMECYCLEMESU_PIN , LOW ); //mesure temps de cycle
    }       
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//                        Méthodes privées                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////
void CRobotJunior::_followTheLigne( byte capteurLigneGauche, byte capteurLigneDroite){
        const int constForceTourne = 20;
        int forceTourne;

        // Serial.println( "Capteur droit = " + String( capteurLigneDroite ) );
        // Serial.print( "D = " + String( capteurLigneDroite ) );
        // Serial.println( "\tG = " + String( capteurLigneGauche ) );
        int obstacle = _usCentre.getDistance();
        
        if ( obstacle > 0 && obstacle < DISTANCE_ARRET ){
            if (_inRun){ //sinon déjà arrêté
                _motG.stop();
                _motD.stop();  
                _buz.tutut(); //tut tut 
                _inRun = false;                
            }
            return;
        } else if( !_inRun){
            _inRun = true;
        }
        if ( capteurLigneDroite == 7 && capteurLigneGauche == 7 ){ //stop if no ground
            _motG.stop();
            _motD.stop(); 
            return;            
        }
        if(( capteurLigneDroite == 0)  &&  ( capteurLigneGauche == 0 )){
            _motG.avance( _vitesseDeBase );
            _motD.avance( _vitesseDeBase );
            _eteindLed();
            if ( _cptPerteLigne++ > CPT_LIG_LOST_MAX ) _lignePerdue=true;
        } else {
            _cptPerteLigne = 0;
            forceTourne = constForceTourne;
            if(capteurLigneDroite > 0){
                if(capteurLigneDroite >= 2 ){
                    forceTourne = forceTourne * 2;
                }
                if(capteurLigneDroite >= 4 ){
                    forceTourne = forceTourne * 2;
                }
                // Serial.println("forceTourne droite = " + String( forceTourne ) );
                _tourneDroite(forceTourne);
                _allumeLedDroite();
            }
            if(capteurLigneGauche > 0){
                forceTourne = constForceTourne;
                if(capteurLigneGauche >= 2 ){
                    forceTourne = forceTourne * 2;
                }
                if(capteurLigneGauche >= 4 ){
                    forceTourne = forceTourne * 2;
                }
                // Serial.println("forceTourne gauche = " + String( forceTourne ) );
                _tourneGauche(forceTourne);
                _allumLedGauche();
            }
        }     
}

bool CRobotJunior::_retriveLigne(){
    _motD.avance( _vitesseDeBase );
    _motG.avance( _vitesGaucheRetrive );
    _cptTour++;
    if( _cptTour >= 240 ){
        _cptTour = 0;
        if (_vitesGaucheRetrive == 0) _vitesGaucheRetrive = 70;
        else _vitesGaucheRetrive +=20;
    }
    byte capteurLigneDroite = _liner.getValueDroite();
    byte capteurLigneGauche = _liner.getValueGauche();
    //_cptRetrieveLigne pour éviter les fausses détections
    if ( capteurLigneDroite != 0 || capteurLigneGauche !=0 ) _cptRetrieveLigne++;
    else _cptRetrieveLigne = 0;
    if ( _cptRetrieveLigne >= 5 ) return true;
    return false;

}



void CRobotJunior::_initLeds(){
    _ledAvantGauche.begin( LED_AVANT_GAUCHE_PIN , 100, 500 );
    _ledAvantDroite.begin( LED_AVANT_DROITE_PIN, 100,500 );
    _ledArriereDroite.begin( LED_ARRIERE_DROITE_PIN );
    _ledArriereGauche.begin( LED_ARRIERE_GAUCHE_PIN );    
    _ledCapteurGauche.begin( LED_SENSOR_GAUCHE_PIN );
    _ledCapteurCentre.begin( LED_SENSOR_CENTRE_PIN );
    _ledCapteurDroite.begin( LED_SENSOR_DROITE_PIN );
    _ledCapteurGauche.off();
    _ledCapteurCentre.off();  
    _ledCapteurDroite.off();    
}

void CRobotJunior::_initSensors(){
    _usGauche.begin( US_SENSOR_GAUCHE_TRIG_PIN, US_SENSOR_GAUCHE_ECHO_PIN, TEMPS_CYCLE );
    _usCentre.begin( US_SENSOR_CENTRE_TRIG_PIN, US_SENSOR_CENTRE_ECHO_PIN, TEMPS_CYCLE );
    _usDroite.begin( US_SENSOR_DROITE_TRIG_PIN, US_SENSOR_DROITE_ECHO_PIN, TEMPS_CYCLE );
    _irGauche.begin( IR_SENSOR_GAUCHE_PIN );
    _irCentre.begin( IR_SENSOR_CENTRE_PIN );
    _irDroite.begin( IR_SENSOR_DROITE_PIN );    
}

void CRobotJunior::_initBuzzer(){
    _buz.begin( BUZZER_PIN );
    _buz.setPeriod( 300 );
    _buz.setFreq(1760);
    _buz.setDuration( 500 );
    _buz.setCount( 2 );
}

void CRobotJunior::_initMotors(){
    _motD.begin( MOTEUR_DROITE_VITS_PIN, MOTEUR_DROITE_SENS_PIN);
    _motG.begin( MOTEUR_GAUCHE_VITS_PIN, MOTEUR_GAUCHE_SENS_PIN);    
}

void CRobotJunior::_updateLeds(){
    _ledAvantGauche.update();
    _ledAvantDroite.update();
    _ledArriereGauche.update();
    _ledArriereDroite.update();
    
    _ledCapteurGauche.update();
    _ledCapteurCentre.update();
    _ledCapteurDroite.update();    
}

void CRobotJunior::_updatesSensors(){
    _usGauche.update();
    _usCentre.update();
    _usDroite.update();
    
    _irGauche.update();
    _irCentre.update();
    _irDroite.update();    
}

void CRobotJunior::_allumLedGauche(){
    _ledAvantDroite.off();
    _ledAvantGauche.on();
    _ledArriereDroite.off(); 
    _ledArriereGauche.on();
   
}

void CRobotJunior::_allumeLedDroite(){
    _ledAvantDroite.on();
    _ledAvantGauche.off();
    _ledArriereDroite.on(); 
    _ledArriereGauche.off();    
}

void CRobotJunior::_allumeDroiteGauche(){
    _ledAvantDroite.on();
    _ledArriereDroite.on();
    _ledAvantGauche.on();
    _ledArriereGauche.on();
}


void CRobotJunior::_eteindLed(){
    _ledAvantDroite.off();
    _ledAvantGauche.off();
    _ledArriereGauche.off();
    _ledArriereDroite.off();
}

void CRobotJunior::_tourneGauche( int force ){
    _motD.avance( _vitesseDeBase + force );
    _motG.avance( _vitesseDeBase - force );
}

void CRobotJunior::_tourneDroite( int force ){
    _motD.avance( _vitesseDeBase - force );
    _motG.avance( _vitesseDeBase + force );    
}

// void CRobotJunior::_buzTutTut(){

    // _buz.setPeriod( 50 );
    // _buz.setFreq(800);
    // _buz.setDuration( 100 );
    // _buz.setCount( 2 );
// }