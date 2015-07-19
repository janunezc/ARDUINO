/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPin 12
#define echoPin 13
#define sensorVinPin 11
#define led1 6
#define led2 2
#define led3 3
#define led4 4
#define led5 5
#define laserPin 7



long previousDistance = 0;
long previousLaserDuration = 0;

void setup() {
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(sensorVinPin, OUTPUT);
    pinMode(laserPin, INPUT);
    
    //POWER SENSOR UP
    digitalWrite(sensorVinPin, HIGH);
}

void loop() {
    long duration, distance;

    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(20); // Added this line
    digitalWrite(trigPin, HIGH);
    
    delayMicroseconds(100); // Added this line
    digitalWrite(trigPin, LOW);
    
   
    duration = pulseIn(echoPin, HIGH);
    
    distance = (duration/2) / 29.1;
    
    long diffDistance = distance - previousDistance;
    if (diffDistance < 0) diffDistance = diffDistance * -1;
    
    if (diffDistance > 5){
        previousDistance = distance;

        for (int i; i<distance/10; i++){
          Serial.print("#");
        }
        Serial.print("|(");
        
        Serial.print(distance);
        Serial.println(")");
    }
}
