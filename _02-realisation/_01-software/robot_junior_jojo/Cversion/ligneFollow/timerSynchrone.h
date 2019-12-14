/**
 @file timerSynchrone.h
 @author J.SORANZO
 @date 14/12/2019
 @copyright 2019 CC0
 @version git versionning
 @brief fihcier d'entête de la classe timerSynchrone du RobotJunior
*/


#ifndef _TIMERSYNCHRONE_H
#define _TIMERSYNCHRONE_H

/**
* @class TimerSynchrone timerSynchrone.h
* @brief Parmet de faire des pauses...

Cette classe utilise le temps de cycle du robot pour mesurer le temps.

La durée maximum est de 65535 cycles du robot ou 65535 ms
*/
class TimerSynchrone{
    public:
        TimerSynchrone();
        void setTempoMillis( unsigned int tempo );
        void setTimerCycles( unsigned int cycles );
        bool isEnded(){ return _ended; }
        
        unsigned int update();
    private:
        unsigned int _dureeCycles;
        
        bool _ended;
    
};

#endif