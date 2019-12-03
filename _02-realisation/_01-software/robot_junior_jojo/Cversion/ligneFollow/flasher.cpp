/**
* @file Flasher.cpp
* @author J.SORANZO & Gilles Debussy
* @date 25/12/2018
* @copyright 2018 CC0
* @version 1.0
* @brief Implementation file of Flasher class 

Orginaly for VOR-O13 project and reused here.
*/
#include "Flasher.h"
#include <Arduino.h>
//#include "debugSerialPort.h"

/** 
 @fn void Flasher::begin( int pin, unsigned long ton, unsigned long toff)
 @brief to prepare Led Flashing
 @param pin the pin number where the LED is connected (anode connection and cathod to ground)
 @param ton time during the LED is switched on in milliseconds
 @param toff time during the LED is switched off in milliseconds
 @return no return value
 This function puts pin in output mode and write it to 0 (low state ie off)
*/
void Flasher::begin( int pin, unsigned long ton, unsigned long toff){
    _pin = pin;
    _ton = ton;
    _toff = toff;
    pinMode( _pin, OUTPUT);
    _ledState = 0;
    _previousMillis = 0;
    _changeStateCpt = 0;
    digitalWrite( _pin, _ledState );
    _allwaysOn = false;
    _running = true;
    _repeat  = 0;
    
}

 void Flasher::onFlash( unsigned long ton ){
    _ton = ton;
    _toff = ton;
    _running = true;
    _repeat = 1;
    _repeatCount = 0;
    _ledState = 0;
    _previousMillis = 0;
    _changeStateCpt = 0;
    digitalWrite( _pin, _ledState );
    _allwaysOn = false;
    // Serial.println( "detection ");
     
 }

void Flasher::on(){ 
    digitalWrite( _pin, HIGH );
    _running = false;
    _allwaysOn = true;
    _ledState = true;
    // Serial.println("flasheron");
}

void Flasher::off(){ 
    digitalWrite( _pin, LOW );
    _running = false;
    _allwaysOn = false;
    _ledState = false;
}

/** 
@fn void Flasher::update()
@brief This function should be call periodicly
@return no param and no return value

Function check time with millis function and switch LED if necessary
*/
void Flasher::update(){
    if ( _allwaysOn ){
        if ( !_ledState ){
            _ledState = 1;
            digitalWrite( _pin, _ledState );
        }
        return;   
    } else {
        if ( _running ){
            if ( _repeat ){
                if ( _repeatCount < _repeat ){
                    if ( (millis()-_previousMillis  > _ton) && (_ledState == 1) ){
                        _ledState = 0;
                        _previousMillis = millis();
                        digitalWrite( _pin, _ledState );
                        _changeStateCpt++;
                        _repeatCount++;
                    } else if ( (millis()-_previousMillis  > _toff) && (_ledState == 0) ){
                        _ledState = 1 ;
                        _previousMillis = millis();
                        digitalWrite( _pin, _ledState );
                        _changeStateCpt++; 
                        // _repeatCount++;                        
                    }
                } else { _running = false; }
            } else { // normal mode
                if ( (millis()-_previousMillis  > _ton) && (_ledState == 1) ){
                    _ledState = 0;
                    _previousMillis = millis();
                    digitalWrite( _pin, _ledState );
                    _changeStateCpt++;
                } else if ( (millis()-_previousMillis  > _toff) && (_ledState == 0) ){
                    _ledState = 1 ;
                    _previousMillis = millis();
                    digitalWrite( _pin, _ledState );
                    _changeStateCpt++;
                }  
  
            }
        }
    }
    
    // if ( _flashingMode ){
        // if ( _repeat ){ //repeat mode
            // if ( _repeatCount < _repeat ){
                // if ( (millis()-_previousMillis  > _ton) && (_ledState == _onLevel) ){
                    // _ledState = _offLevel;
                    // _previousMillis = millis();
                    // _ioexp.digitalWrite( _pin, _ledState );
                    // _changeStateCpt++;
                    // _repeatCount++;
                // } else if ( (millis()-_previousMillis  > _toff) && (_ledState == _offLevel) ){
                    // _ledState = _onLevel ;       
                    // _previousMillis = millis();
                    // _ioexp.digitalWrite( _pin, _ledState );
                    // _changeStateCpt++; 
                // } 
            // } else if ( millis()-_previousPeriod > _period ){
                // _previousPeriod = millis();
                // _repeatCount = 0;
                // _previousMillis = millis();
            // }
            
        // } else { //normal mode
            // if ( (millis()-_previousMillis  > _ton) && (_ledState == _onLevel) ){
                // _ledState = _offLevel;
                // _previousMillis = millis();
                // _ioexp.digitalWrite( _pin, _ledState );
                // _changeStateCpt++;
            // } else if ( (millis()-_previousMillis  > _toff) && (_ledState == _offLevel) ){
                // _ledState = _onLevel ;       
                // _previousMillis = millis();
                // _ioexp.digitalWrite( _pin, _ledState );
                // _changeStateCpt++;
            // }    
        // }      
    // }    
    
    
    
    
    
}
/** 
@fn void Flasher::stop()
@brief this function stop LED 
@return no param and no return value

Warning this function doesn't prevent update() to work (except that the pin is in input mode)
*/
void Flasher::stop(){
    digitalWrite( _pin, 0 );
    _ledState = 0;
    pinMode( _pin, INPUT );
    _changeStateCpt = 0;
    _running = false;
}