/**
 @file ligneFollow.ino
 @author J.SORANZO
 @date 26/10/2019
 @copyright 2019 CC0
 @version 
 @brief Permit C version ligne follower in ARDUINO
*/

#include "config.h"
// #include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include "robot.h"


// #include <SPI.h>
#include "RF24.h"

//RH_ASK (uint16_t speed=2000, uint8_t rxPin=11, uint8_t txPin=12, uint8_t pttPin=10, bool pttInverted=false)
// 2000 bits/s <=> 500us/bits <=> 5ms/octet
#define RSSPEED 230400

#define TAILLE_TRAME 11 //caractères

CRobotJunior robot;
// RH_ASK driver(2000, TLMRXPIN, TLMTXPIN, 0); // 19 txpin

//A0 to sens batterie via un pont diviseur par 2 ou A1 VIn passe pas loin

// const unsigned int vitesseDeBase = 10;

unsigned long prevMillis;
#define LEDVERIF 11

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1; // ie Node2

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
// RF24 radio(7,8); 
RF24 radio(48,49); // verion robot maquette
/**********************************************************/

byte addresses[][6] = {"Node1","Node2"};
bool role = 0;

void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
    robot.init( TEMPS_CYCLE );
    // pinMode(LEDVERIF, OUTPUT);
    // if (!driver.init())
    // Serial.println("init failed");
    prevMillis = millis();

    radio.begin();

    // Set the PA Level low to prevent power supply related issues since this is a
    // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
    radio.setPALevel(RF24_PA_MAX);
    if( radio.setDataRate( RF24_2MBPS ) ) Serial.println("speed is now 2Mbps");
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
    Serial.print("Je suis le node : ");Serial.println( (char *)addresses[1] );
    if ( !radio.isChipConnected() ){
        Serial.println(" Pb connection ! Aborted.");
        for(;;);
    } else {
        Serial.println( "appareil bien connecte.");
        // for(;;);
    }  
    Serial.print("pa level : "); Serial.println( radio.getPALevel() );
    Serial.print("Payloadsize : ");Serial.println( radio.getPayloadSize() );
    
}

bool ledState;
char trame[ TAILLE_TRAME + 1 ];
byte cpt = 0;
void loop(){
    robot.update();
    sprintf( trame, "%03d,3.2,0.0", cpt, 2 );
    if ( millis() - prevMillis >= 100 ){
        prevMillis = millis();
        cpt++;
        // if (cpt==10)cpt = 0;
        Serial.print(F("Now sending : "));
        Serial.print( trame );
        Serial.print( " : taille trame  : "); Serial.print( strlen( trame) );
        Serial.print(" : ");
        if (!radio.write( trame, TAILLE_TRAME )){
            Serial.println(F("failed"));
        } else {
            Serial.println();
        }
    }
    
    


    // // unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete
    // unsigned long start_time[2];
    // start_time[0]= micros();                             // Take the time, and send it.  This will block until complete
    // start_time[1]= millis();
    // unsigned long tx_time = micros();
     // if (!radio.write( start_time, 2*sizeof(unsigned long) )){
       // Serial.println(F("failed"));
     // }
    // // Serial.print("TX time = ");Serial.println( micros() - tx_time );
    // radio.startListening();                                    // Now, continue listening
    
    // unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    // boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    // while ( ! radio.available() ){                             // While nothing is received
      // if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          // timeout = true;
          // break;
      // }      
    // }
        
    // if ( timeout ){                                             // Describe the results
        // Serial.println(F("Failed, response timed out."));
    // }else{
        // unsigned long got_time[2];                                 // Grab the response, compare, and send to debugging spew
        // radio.read( got_time, 2*sizeof(unsigned long) );
        // unsigned long end_time = micros();
        
        // // Spew it
        // Serial.print(F("Sent "));
        // Serial.print(start_time[0]);
        // Serial.print(start_time[1]);
        // Serial.print(F(", Got response "));
        // Serial.print(got_time[0]);
        // Serial.print(got_time[1]);
        // Serial.print(F(", Round-trip delay "));
        // Serial.print(end_time-start_time[0]);
        // Serial.println(F(" microseconds"));
    // }

    // // Try again 1s later
    // delay(1000);
  // }

    
}

