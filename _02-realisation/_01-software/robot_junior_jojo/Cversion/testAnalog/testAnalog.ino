#define RSSPEED 230400

void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
     
}


float bat;
byte batEnt;
byte batDec;
byte cpt;
char trame[11+1];
void loop(){
    bat = (analogRead(A0)*5.0/1024.0)/.586;
    Serial.print( "Tension mesuree: " ); Serial.print( bat );
    batEnt = int(bat);
    Serial.print( " entiere = " ); Serial.print( batEnt );
    batDec = int((bat - batEnt)*10.0);
    Serial.print( " decimale = " ); Serial.println( batDec );

    sprintf( trame, "%03d,%d,%d,%d.%d"
                , cpt++
                , 4
                , 2
                , batEnt
                , batDec );
    Serial.print( " trame = " ); Serial.println( trame );
    delay(1000);
}