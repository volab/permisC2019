/**
 @file buzer.h
 @author J.SORANZO
 @date 01/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Fichier d'entête de la classe CBuzer
*/

#include <Arduino.h>

#ifndef CBUZER_H
#define CBUZER_H

class CBuzzer{
    public:
        void begin( int pin, unsigned int freq = 440, unsigned long duree = 500
                    , unsigned long period = 1000 );
        void update();
        void setPeriod( unsigned long period){ _period = period; }
        void setFreq( unsigned int freq){ _freq = freq; }
        void setDuration( unsigned long duree ){ _duree = duree; }
        void setCount( unsigned int count ){ _cpt = _count = count; };
	
    
    private:
        int _pin;
        unsigned int _freq;
        unsigned long _duree;
        unsigned long _period;
        unsigned long _prev_millis;
        unsigned int _count;
        unsigned int _cpt;
    
    
    
};



#endif