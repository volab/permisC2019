/**
 @file robot.cpp
 @author J.SORANZO
 @date 02/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief fichier d'implémentation de la classe CRobotJunior
*/

#include "robot.h"
extern RF24 radio;

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
}

void CRobotJunior::update(){
    _updateLeds();
    // _updatesSensors();
    _liner.forceUpdate();
    _buz.update(); 
    if ( millis() - _prevMillis > _tempsCycle ){
        digitalWrite( TIMECYCLEMESU_PIN , HIGH ); //to mesure cycle time
        _prevMillis = millis();
        const int constForceTourne = 20;
        int forceTourne;
        byte capteurLigneDroite = _liner.getValueDroite();
        byte capteurLigneGauche = _liner.getValueGauche();
        // Serial.println( "Capteur droit = " + String( capteurLigneDroite ) );
        // Serial.print( "D = " + String( capteurLigneDroite ) );
        // Serial.println( "\tG = " + String( capteurLigneGauche ) );
        if ( capteurLigneDroite == 7 && capteurLigneGauche == 7 ){ //stop if no ground
            _motG.stop();
            _motD.stop(); 
            return;            
        }
        if(( capteurLigneDroite == 0)  &&  ( capteurLigneGauche == 0 )){
            _motG.avance( _vitesseDeBase );
            _motD.avance( _vitesseDeBase );
            _eteindLed();

        } else {
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
        // char trame[ TAILLE_TRAME + 1 ];
        _bat = (analogRead(A0)*5.0/1024.0)/.586;
        _batEnt = int( _bat );
        _batDec = int( (_bat - _batEnt) *10.0 );
        unsigned long temps = millis();
        char c = '*';
        sprintf( _trame, "%06lu,%d,%d,%d.%d,%c"
                    , temps
                    , capteurLigneGauche
                    , capteurLigneDroite
                    , _batEnt
                    , _batDec
                    , c );
        // sprintf( _trame, "%03d,%d,%d,3.0"
                    // , _cpt++
                    // , capteurLigneGauche
                    // , capteurLigneDroite );
        // radio.write( _trame, TAILLE_TRAME );
        Serial.println(_trame);
        
        digitalWrite( TIMECYCLEMESU_PIN , LOW );
    }       
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//                        Méthodes privées                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////


void CRobotJunior::_initLeds(){
    _ledAvantGauche.begin( LED_AVANT_GAUCHE_PIN , 100, 500 );
    _ledAvantDroite.begin( LED_AVANT_DROITE_PIN, 100,500 );
    _ledArriereDroite.begin( LED_ARRIERE_DROITE_PIN );
    _ledArriereGauche.begin( LED_ARRIERE_GAUCHE_PIN );    
    _ledCapteurGauche.begin( LED_SENSOR_GAUCHE_PIN );
    _ledCapteurCentre.begin( LED_SENSOR_CENTRE_PIN );
    _ledCapteurDroite.begin( LED_SENSOR_DROITE_PIN );
    _ledCapteurGauche.on();
    _ledCapteurCentre.on();  
    _ledCapteurDroite.on();    
}

void CRobotJunior::_initSensors(){
    _usGauche.begin( US_SENSOR_GAUCHE_TRIG_PIN, US_SENSOR_GAUCHE_ECHO_PIN );
    _usCentre.begin( US_SENSOR_CENTRE_TRIG_PIN, US_SENSOR_CENTRE_ECHO_PIN );
    _usDroite.begin( US_SENSOR_DROITE_TRIG_PIN, US_SENSOR_DROITE_ECHO_PIN );
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