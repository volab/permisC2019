/**
 @file motor.cpp
 @author J.SORANZO
 @date 2/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief fichier d'implémentation de la classe CMotor
*/

#include "motor.h"

void CDCMotor::begin( int vitessePin, int directionPin ){
    _directionPin = directionPin;
    _vitessePin = vitessePin;
    _vitesse = 0;
    pinMode( _directionPin, OUTPUT );
    pinMode( _vitessePin, OUTPUT );
}


void CDCMotor::roule(){
    digitalWrite( _directionPin, _sens );
    analogWrite( _vitessePin, _vitesseVsSens );
    
}
void CDCMotor::avance(){
    setDirection( EN_AVANT );
    roule();
}
void CDCMotor::recule(){
    setDirection( EN_ARRIERE );
    roule();    
}

void CDCMotor::avance( unsigned int vitesse ){
    setVitesse( vitesse );
    avance();
}
void CDCMotor::recule( unsigned int vitesse ){
    setVitesse( vitesse );
    recule();    
}


void CDCMotor::stop(){
    digitalWrite( _directionPin, 0 );
    analogWrite( _vitessePin, 0 );    
    
}

void CDCMotor::setVitesse( unsigned int vitesse ){
    if ( (_vitesse >= 85) || (_vitesse <= 255 ) ){
        _vitesse = vitesse;
        if ( _sens == EN_AVANT){
            _vitesseVsSens = _vitesse;
        } else {
            _vitesseVsSens = 255-_vitesse; 
        }   
    }
    
}

void CDCMotor::setDirection( byte sens ){
    _sens = sens;
    if ( _sens == EN_AVANT){
        _vitesseVsSens = _vitesse;
    } else {
        _vitesseVsSens = 255-_vitesse; 
    } 
}