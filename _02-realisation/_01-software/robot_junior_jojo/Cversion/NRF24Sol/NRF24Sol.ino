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

#define PC_COM_SPEED 230400
#define TAILLE_TRAME 11 //caractères

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

  
  // Open a writing and reading pipe on each radio, with opposite addresses
  // if(radioNumber){
    // radio.openWritingPipe(addresses[1]);
    // radio.openReadingPipe(1,addresses[0]);
    // Serial.print("Je suis le node : ");Serial.println( (char *)addresses[1] );
  // }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
    Serial.print("Je suis le node : ");Serial.println( (char *)addresses[0] );
  // }
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
  
  
/****************** Ping Out Role ***************************/  
// if (role == 1)  {
    // Serial.println("TX role");
    // radio.stopListening();                                    // First, stop listening so we can talk.
    
    
    // Serial.println(F("Now sending"));

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



/****************** Pong Back Role ***************************/

if ( role == 0 ){ //if à supprimer 
    // unsigned long got_time;
    // unsigned long got_time[2];
    char trame[ TAILLE_TRAME+1 ];
    trame[ TAILLE_TRAME ] = 0;
    // Serial.print("Role peroquet.");
    // Serial.println( cpt++);
    if( radio.available()){
        // Variable for the received timestamp
        while (radio.available()) {                                   // While there is data ready
            // radio.read( got_time, 2*sizeof(unsigned long) );             // Get the payload
            radio.read( trame, TAILLE_TRAME );             // Get the payload
        }
        
        // radio.stopListening();                                        // First, stop listening so we can talk   
        // radio.write( got_time, 2*sizeof(unsigned long) );              // Send the final one back.      
        // radio.startListening();                                       // Now, resume listening so we catch the next packets.     
        Serial.println(trame);
        // Serial.println(got_time);  
    }
}




/****************** Change Roles via Serial Commands ***************************/

  // if ( Serial.available() )
  // {
    // char c = toupper(Serial.read());
    // if ( c == 'T' && role == 0 ){      
      // Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      // role = 1;                  // Become the primary transmitter (ping out)
    
   // }else
    // if ( c == 'R' && role == 1 ){
      // Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));      
       // role = 0;                // Become the primary receiver (pong back)
       // radio.startListening();
       
    // }
  // }


} // Loop

