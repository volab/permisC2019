/**
 @file NRF24Sol.ino
 @author J.SORANZO
 @date 16/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Le but est de récupérer les paramètres du robot vie un module NRF24L01 et de les
 retransmettre au PC hote vie l'USB. Ce programme a été créé à partir de l'exemple décrit
 ci-dessous.
*/
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

#define PC_COM_SPEED 460800
#define TAILLE_TRAME 16 //caractères

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0; // ie Node 1

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8); 
// RF24 radio(48,49); // verion robot maquette
/**********************************************************/

byte addresses[][6] = {"Node1","Node2"};

// Used to control whether this node is sending or receiving
bool role = 0;
unsigned long cpt = 0;
void setup() {
    Serial.begin(PC_COM_SPEED);
    Serial.println(F("RF24/Station sol du robot Junior."));  
    radio.begin();

    // Set the PA Level low to prevent power supply related issues since this is a
    // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
    radio.setPALevel(RF24_PA_MAX);
    if( radio.setDataRate( RF24_2MBPS ) ) Serial.println("speed is now 2Mbps");

    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
    Serial.print("Je suis le node : ");Serial.println( (char *)addresses[0] );

    if ( !radio.isChipConnected() ){
        Serial.println(" Pb connection ! Aborted.");
        for(;;);
    } else {
        Serial.println( "appareil bien connecte.");
        // for(;;);
    }  
    Serial.print("pa level : "); Serial.println( radio.getPALevel() );
    Serial.print("Payloadsize : ");Serial.println( radio.getPayloadSize() );

    // Start the radio listening for data
    radio.startListening();
}

void loop() {
  
if ( role == 0 ){ //if à supprimer 
    char trame[ TAILLE_TRAME+1 ];
    trame[ TAILLE_TRAME ] = 0;
    if( radio.available()){
        // Variable for the received timestamp
        while (radio.available()) {                                   // While there is data ready
            radio.read( trame, TAILLE_TRAME );             // Get the payload
        } 
        Serial.println(trame); 
    }
}

} // Loop

