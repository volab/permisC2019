/**
 @file APC220Test.ino
 @author J.SORANZO
 @date 08/11/2019
 @copyright 2019 CC0
 @version git versionning
 @brief Test des modules de transmission ACP220
*/

#define RSSPEED 9600
#define RSPEED1 9600

void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
    Serial1.begin( RSPEED1 );
}

unsigned long cpt;
void loop(){
    Serial.println( "emission" );
    Serial1.println( " test " + String( cpt++ ) );
    delay(1000);
}