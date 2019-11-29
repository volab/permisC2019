/**
 @file usSensor.cpp
 @author J.SORANZO
 @date 26/10/2019
 @copyright 2019 CC0
 @version git versionning
 @brief implementation file of the class CUsSensor
*/

#include "usSensor.h"
#include <Arduino.h>

void CUsSensor::begin( int trigPin, int echoPin, unsigned long samplePeriod ){
    _trigPin = trigPin;
    _echoPin = echoPin;
    _samplePeriod = samplePeriod;
    pinMode( _trigPin, OUTPUT );
    pinMode( _echoPin, INPUT );
    _distance = 0;
}

void CUsSensor::update(){
    if ( millis()-_previousMillis  > _samplePeriod ){ 
        _previousMillis = millis();
        digitalWrite( _trigPin,LOW);
        delayMicroseconds(2);
        digitalWrite( _trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite( _trigPin,LOW);
        
        
        _distance = (int)( pulseIn(_echoPin,HIGH,2900)/58.0 );
        //distance =  0 on timeout;
        //30.000us <=> 525cm
        //2900us <=> 50cm
    } 
}


int CUsSensor::getDistance(){
    return _distance;
}