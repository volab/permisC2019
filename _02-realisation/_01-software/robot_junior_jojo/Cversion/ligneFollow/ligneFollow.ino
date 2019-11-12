/**
 @file ligneFollow.ino
 @author J.SORANZO
 @date 26/10/2019
 @copyright 2019 CC0
 @version 
 @brief Permit C version ligne follower in ARDUINO
*/

#include "config.h"
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include "robot.h"

//RH_ASK (uint16_t speed=2000, uint8_t rxPin=11, uint8_t txPin=12, uint8_t pttPin=10, bool pttInverted=false)
// 2000 bits/s <=> 500us/bits <=> 5ms/octet
#define RSSPEED 9600

CRobotJunior robot;
// RH_ASK driver(2000, TLMRXPIN, TLMTXPIN, 0); // 19 txpin

//A0 to sens batterie via un pont diviseur par 2 ou A1 VIn passe pas loin

// const unsigned int vitesseDeBase = 10;

unsigned long prevMillis;
#define LEDVERIF 11
void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
    robot.init( TEMPS_CYCLE );
    // pinMode(LEDVERIF, OUTPUT);
        // if (!driver.init())
         // Serial.println("init failed");

    
}

bool ledState;
void loop(){
        robot.update();
    // const char *msg = "hello"; // 5x5ms=25ms @2000bits/s

    // driver.send((uint8_t *)msg, strlen(msg));
    // driver.waitPacketSent();
    // delay(1000);
    // ledState = !ledState;
    // digitalWrite( LEDVERIF, ledState );

    
}

