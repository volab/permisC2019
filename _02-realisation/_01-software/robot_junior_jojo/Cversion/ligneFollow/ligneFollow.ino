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
#include "RF24.h"

#define RSSPEED 230400

// #define TAILLE_TRAME 11 //caractères

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
    prevMillis = millis();

    radio.begin();
    randomSeed( analogRead(A4) );
    
    // Set the PA Level low to prevent power supply related issues since this is a
    // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
    radio.setPALevel(RF24_PA_MAX);
    if( radio.setDataRate( RF24_2MBPS ) ) Serial.println("speed is now 2Mbps");
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
    radio.enableDynamicAck();
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
    robot.update(); // Eh oui ! Il n'y a que ça dans la boucle loop
}

