#define RSSPEED 9600

void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
     
}

void loop(){
    Serial.print( "Tension mesuree: " ); Serial.println( (analogRead(A0)*5.0/1024.0)/.586 );
    delay(1000);
}