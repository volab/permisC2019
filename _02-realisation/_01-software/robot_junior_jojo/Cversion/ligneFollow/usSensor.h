/**
 @file usSensor.h
 @author J.SORANZO
 @date 26/10/2019
 @copyright 2019 CC0
 @version 
 @brief header file of the class CUsSensor
*/

#ifndef CUSSENSOR_H
#define CUSSENSOR_H



class CUsSensor{
    public:
        void begin( int trigPin, int echoPin, unsigned long samplePeriod = 5 );
        void update();
        int getDistance();
    
    private:
        int _trigPin;
        int _echoPin;
        unsigned long _previousMillis;
        unsigned long _samplePeriod;
        int _distance;
        
};


#endif