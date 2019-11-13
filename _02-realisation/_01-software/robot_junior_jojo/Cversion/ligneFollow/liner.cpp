/**
 @file liner.cpp
 @author J.SORANZO
 @date 27/10/2019
 @copyright 2019 CC0
 @version git versionning
 @brief fichier d'implémentation de la classe CRjLiner
*/

#include "liner.h"


void CRjLiner::begin( 
      int pinGaucheExt
    , int pinGaucheMid
    , int pinGaucheCentre
    , int pinDroiteCentre
    , int pinDroiteMid
    , int pinDroiteExt )
{
    _irSensor[ 0 ].begin( pinGaucheCentre    );
    _irSensor[ 1 ].begin( pinGaucheMid    );
    _irSensor[ 2 ].begin( pinGaucheExt );
    
    _irSensor[ 3 ].begin( pinDroiteCentre );
    _irSensor[ 4 ].begin( pinDroiteMid    );
    _irSensor[ 5 ].begin( pinDroiteExt    );   
    _value = 0;
}

void CRjLiner::update(){
        if ( millis()-_previousMillis  > _samplePeriod ){ 
            _previousMillis = millis();
            forceUpdate();
        }
} 

void CRjLiner::forceUpdate(){
    _value = 0;
    for ( int i = 0; i < 6 ; i++ ){
        _value += ( (_irSensor[i].directRead()) << i );
    }
    _valueD = _value / 8;
    _valueG = _value % 8;    
}