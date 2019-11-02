/**
 @file ligneFollow.ino
 @author J.SORANZO
 @date 26/10/2019
 @copyright 2019 CC0
 @version 
 @brief Permit C version ligne follower in ARDUINO
*/

#include "config.h"
#include "robot.h"


#define RSSPEED 9600

CRobotJunior robot;

const unsigned int vitesseDeBase = 100;

unsigned long prevMillis;

void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
    robot.init( TEMPS_CYCLE );
    // initLeds();
    // delay(300);
    // initSensors();
    // liner.begin(
          // LINESENSOR_GAUCHE_EXTERNE_PIN
        // , LINESENSOR_GAUCHE_MILIEUX_PIN
        // , LINESENSOR_GAUCHE_INTERNE_PIN
        // , LINESENSOR_DROITE_INTERNE_PIN 
        // , LINESENSOR_DROITE_MILIEUX_PIN
        // , LINESENSOR_DROITE_EXTERNE_PIN    
    // );
    
    // buz.begin( 4 );
    // buz.setPeriod( 300 );
    // buz.setFreq(1760);
    // buz.setDuration( 500 );
    // buz.setCount( 2 );
    // prevMillis = millis();
    
    // motD.begin( MOTEUR_DROITE_VITS_PIN, MOTEUR_DROITE_SENS_PIN);
    // motG.begin( MOTEUR_GAUCHE_VITS_PIN, MOTEUR_GAUCHE_SENS_PIN);
    
}

void loop(){
        robot.update();
    
    // // Serial.print( "Distance au centre = " + String( usCentre.getDistance() ) +" cm" );
    // // Serial.print( "Liner value G = " + String( liner.getValueGauche() ) );
    // // Serial.print( "\tD = " + String( liner.getValueDroite() ) );
    // // Serial.println( "\tbrute = " + String( liner.getValue() ) );
    
    // if ( irGauche.getState() ) ledCapteurGauche.on();
    // else ledCapteurGauche.off();
    // if ( irCentre.getState() ) ledCapteurCentre.on();
    // else ledCapteurCentre.off();
    // if ( irDroite.getState() ) ledCapteurDroite.on();
    // else ledCapteurDroite.off();

    // if ( millis() - prevMillis > TEMPS_CYCLE ){
        // prevMillis = millis();
        // const int constForceTourne = 20;
        // int forceTourne;
        // byte capteurLigneDroite = liner.getValueDroite();
        // byte capteurLigneGauche = liner.getValueGauche();
        // Serial.print( "D = " + String( capteurLigneDroite ) );
        // Serial.println( "\tG = " + String( capteurLigneGauche ) );
        // if(( capteurLigneDroite == 0)  &&  ( capteurLigneGauche == 0 )){
            // motG.avance( vitesseDeBase );
            // motD.avance( vitesseDeBase );
            // eteindLed();

        // } else {
            // forceTourne = constForceTourne;
            // if(capteurLigneDroite > 0){
                // if(capteurLigneDroite >= 2 ){
                    // forceTourne = forceTourne * 2;

                // }
                // if(capteurLigneDroite >= 4 ){
                    // forceTourne = forceTourne * 2;

                // }
                // tourneDroite(forceTourne);
                // allumeLedDroite();

            // }
            // if(capteurLigneGauche > 0){
                // forceTourne = constForceTourne;
                // if(capteurLigneGauche >= 2 ){
                            // forceTourne = forceTourne * 2;

                        // }
                        // if(capteurLigneGauche >= 4 ){
                    // forceTourne = forceTourne * 2;

                // }
                // tourneGauche(forceTourne);
                // allumLedGauche();

            // }
        // }

    // }    
    
}

// void allumLedGauche(){
    // ledAvantDroite.off();
    // ledAvantGauche.on();
    // ledArriereDroite.off(); 
    // ledArriereGauche.on();
   
// }

// void allumeLedDroite(){
    // ledAvantDroite.on();
    // ledAvantGauche.off();
    // ledArriereDroite.on(); 
    // ledArriereGauche.off();    
// }

// void eteindLed(){
    // ledAvantDroite.off();
    // ledAvantGauche.off();
    // ledArriereGauche.off();
    // ledArriereDroite.off();
// }

// void tourneGauche( int force ){
    // motD.avance( vitesseDeBase + force );
    // motG.avance( vitesseDeBase - force );
// }

// void tourneDroite( int force ){
    // motD.avance( vitesseDeBase - force );
    // motG.avance( vitesseDeBase + force );    
// }

// void initLeds(){
    // ledAvantGauche.begin( LED_AVANT_GAUCHE_PIN , 100, 500 );
    // ledAvantDroite.begin( LED_AVANT_DROITE_PIN, 100,500 );
    // ledCapteurGauche.begin( LED_SENSOR_GAUCHE_PIN );
    // ledCapteurCentre.begin( LED_SENSOR_CENTRE_PIN );
    // ledCapteurDroite.begin( LED_SENSOR_DROITE_PIN );
    // ledCapteurGauche.on();
    // ledCapteurCentre.on();  
    // ledCapteurDroite.on();
// }

// void initSensors(){
    // usGauche.begin( US_SENSOR_GAUCHE_TRIG_PIN, US_SENSOR_GAUCHE_ECHO_PIN );
    // usCentre.begin( US_SENSOR_CENTRE_TRIG_PIN, US_SENSOR_CENTRE_ECHO_PIN );
    // usDroite.begin( US_SENSOR_DROITE_TRIG_PIN, US_SENSOR_DROITE_ECHO_PIN );
    // irGauche.begin( IR_SENSOR_GAUCHE_PIN );
    // irCentre.begin( IR_SENSOR_CENTRE_PIN );
    // irDroite.begin( IR_SENSOR_DROITE_PIN );
    
// }