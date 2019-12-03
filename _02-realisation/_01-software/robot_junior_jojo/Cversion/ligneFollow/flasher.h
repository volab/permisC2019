//--------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
// Class flasher de led avec ton et toff différent
//--------------------------------------------------------------------------------------------------
/**
 @file Flasher.h
 @brief Header file of the Flasher class
*/

#ifndef LEDFLASHER_H
#define LEDFLASHER_H




/**
* @class Flasher Flasher.h
* @brief a Class to flash a simple LED with direct connections
 @details
This class is for flashing simple led with no delay with diffrents ton and toff

In setup or elsewhere create a Flasher instance  i and call i.begin( pin, ton, toff )

They are no default values.

In a loop call i.update();

To return to led off and stop flashing you can call i.stop()

i.getChangeStateCpt() can be used to flash a certain number of times

 @todo implement begin( ton, toff, repeat, period ) exemple 3 short flash every 3 seconds
 @todo implement the same but when on, exemple 3 short off every 3 seconds

*/
class Flasher {
    public:
        void stop();
        Flasher(){};
        void begin( int pin, unsigned long ton = 0, unsigned long toff = 0 );
        void onFlash( unsigned long ton );
        void update();
        int getChangeStateCpt(){ return _changeStateCpt; }/**< @brief to stop flashing after a certain number of times*/
        void allwaysOn(){_allwaysOn = true;}
        void on();
        void off();
    
    private:
        unsigned long _ton;
        unsigned long _toff;
        int _pin;
        unsigned long _previousMillis;
        int _ledState ;
        unsigned long _changeStateCpt;
        bool _allwaysOn = false;
        bool _running = false;
        unsigned int _repeat;
        unsigned int _repeatCount;
    
};

#endif