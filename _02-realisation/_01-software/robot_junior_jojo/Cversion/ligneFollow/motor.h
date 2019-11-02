/**
 @file motor.h
 @author J.SORANZO
 @date 1/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Fichier d'entête de la classe DC motor CDCMotor
 
 En arriere la vitesse est inversée de 0 rapide à 170lent
 en avant la place utile va de 255 rapide à 85
 
 
 @code {.cpp}
    motG.begin( MOTEUR_GAUCHE_VITS_PIN, MOTEUR_GAUCHE_SENS_PIN);
    motG.setDirection( CDCMotor::EN_AVANT );
        // motG.setVitesse( 0 );
        // motG.roule();    
    for ( int i = 85; i < 255 ; i +=5 ){
        motG.setVitesse( i );
        motG.roule();
        Serial.println( "vitesse = " + String( i ) );
        delay(100);
    }
    
    
    motD.begin( MOTEUR_DROITE_VITS_PIN, MOTEUR_DROITE_SENS_PIN);
    motD.setVitesse( 128 );
    motD.setDirection( CDCMotor::EN_AVANT );
    motD.roule();    
    delay( 1000 );
    motG.stop();
    
    delay(500);
    motG.setVitesse( 125 );
    motG.avance();
    delay( 500 );
    motG.stop();
    motG.recule( 255 );
    delay( 800 );
    motG.stop();
 
 @endcode 

*/

#include <Arduino.h>

#ifndef _CMOTOR_H
#define _CMOTOR_H



class CDCMotor{
    public:
        enum{ EN_AVANT, EN_ARRIERE };
        void begin( int vitessePin, int directionPin );
        void setVitesse( unsigned int vitesse );
        void setDirection( byte sens );
        void roule();
        void avance( );
        void recule( );
        void avance( unsigned int vitesse );
        void recule( unsigned int vitesse );
        void stop();

        
    private:
        unsigned int _vitesse;
        unsigned int _vitesseVsSens;
        byte _sens;
        int _vitessePin;
        int _directionPin;
};

#endif