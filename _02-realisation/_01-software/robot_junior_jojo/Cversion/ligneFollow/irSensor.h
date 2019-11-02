/**
 @file irSensor.h
 @author J.SORANZO
 @date 27/10/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Fichier d'entête de la classe CIrSensor
*/

#ifndef CIRSENSOR_H
#define CIRSENSOR_H



class CIrSensor{
    public:
        void begin( int pin, unsigned long samplePeriod = 8 );
        void update();
        bool getState(){ return _state; } // state = on <=> object detected
        bool directRead();
    private:
        int _pin;
        unsigned long _previousMillis;
        bool _state;
        unsigned int _samplePeriod;
};




#endif