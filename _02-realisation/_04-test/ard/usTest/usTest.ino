#define RSSPEED 115200

int trig = 13;
int echo = 15;

float getDistance(int trig,int echo){
    pinMode(trig,OUTPUT);
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    pinMode(echo, INPUT);
    return pulseIn(echo,HIGH,30000)/58.0;
}

void setup(){
    Serial.begin( RSSPEED );
    Serial.println( "Sketch start...");
    
    
}

void loop(){
    Serial.println( "distance = " + String( getDistance( trig, echo ) ) );
    delay(500);
}