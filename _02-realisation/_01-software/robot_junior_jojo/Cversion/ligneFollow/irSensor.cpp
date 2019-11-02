/**
 @file irSensor.cpp
 @author J.SORANZO
 @date 27/10/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Fichier d'implementation de la classe CIrSensor
*/

#include "irSensor.h"
#include <Arduino.h>

void CIrSensor::begin( int pin, unsigned long samplePeriod = 8 ){
    _pin = pin;
    _samplePeriod = samplePeriod;
    pinMode( _pin, INPUT );
}


void CIrSensor::update(){
    if ( millis()-_previousMillis  > _samplePeriod ){ 
        _previousMillis = millis();
        _state = !digitalRead( _pin );
    }
    
}

bool CIrSensor::directRead(){ return digitalRead( _pin ); }