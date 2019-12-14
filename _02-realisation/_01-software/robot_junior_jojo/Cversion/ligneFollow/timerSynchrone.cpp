/**
 @file timerSynchrone.cpp
 @author J.SORANZO
 @date _date
 @copyright 2019 CC0
 @version git versionning
 @brief fichier d'implémentation de la classe TimerSynchrone
*/

#include "timerSynchrone.h"

TimerSynchrone::TimerSynchrone(){
    _dureeCycles = 0;

    _ended = true;
}

void TimerSynchrone::setTimerCycles( unsigned int cycles ){
    _dureeCycles = cycles;
    _ended = false;
}

unsigned int TimerSynchrone::update(){
    unsigned int returnVal = 0;
    if ( _dureeCycles ){
        returnVal = _dureeCycles--;
        if ( !_dureeCycles ) _ended = true;  
    }
    return returnVal;
    
}

void TimerSynchrone::setTempoMillis( unsigned int tempo ){
    
}