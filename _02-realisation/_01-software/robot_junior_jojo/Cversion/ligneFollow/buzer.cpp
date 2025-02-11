/**
 @file _fileName_cpp_or_h
 @author J.SORANZO
 @date _date
 @copyright 2019 CC0
 @version git versionning
 @brief _briefText
*/

#include "buzer.h"

void CBuzzer::begin( int pin, unsigned int freq, unsigned long duree, unsigned long period ){
    _pin = pin;
    _freq = freq;
    _duree = duree;
    _period = period;
    _prev_millis = millis();
    _count = 0; 
}

void CBuzzer::update(){
    if ( millis() - _prev_millis > _period + _duree ){
        _prev_millis = millis();
        if ( _count != 0 ){
            if ( _cpt != 0 ){
                tone( _pin, _freq, _duree);
                --_cpt;   
            } else noTone( _pin );
        } else {
            tone( _pin, _freq, _duree);
        }
            
    }
}


void CBuzzer::tutut(){
    setPeriod( 50 );
    setFreq(800);
    setDuration( 100 );
    setCount( 2 );    
}

void CBuzzer::ligneLostSound(){
    setPeriod( 300 );
    setFreq(400);
    setDuration( 300 );
    setCount( 4 );      
}
