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

#define trigPin 13
#define echoPin 12
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
    pinMode(laserPin, INPUT);
    
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);

}

void loop() {
    long duration, distance, laserDuration, diffLaserDuration;
    digitalWrite(trigPin, LOW);  // Added this line
    delayMicroseconds(20); // Added this line
    digitalWrite(trigPin, HIGH);
    
    delayMicroseconds(100); // Added this line
    digitalWrite(trigPin, LOW);
    
   
    duration = pulseIn(echoPin, HIGH);
    laserDuration = pulseIn(laserPin, LOW, 5000);    
    
    diffLaserDuration = laserDuration - previousLaserDuration;
    if (diffLaserDuration <0) diffLaserDuration = diffLaserDuration * -1;
    
    if(diffLaserDuration >100 || laserDuration == 0) {
      previousLaserDuration = laserDuration;
      Serial.print("Laser Duration: ");
      Serial.println(laserDuration);
    }
      distance = (duration/2) / 29.1;
    
    if (distance < 600) {  // This is where the LED On/Off happens
        digitalWrite(led5,HIGH); // When the Red condition is met, the Green LED should turn off
    } else {
        digitalWrite(led5,LOW);
    }
    
    if (distance < 400) {  // This is where the LED On/Off happens
        digitalWrite(led4,HIGH); // When the Red condition is met, the Green LED should turn off
    } else {
        digitalWrite(led4,LOW);
    }
    
        if (distance < 300) {  // This is where the LED On/Off happens
        digitalWrite(led3,HIGH); // When the Red condition is met, the Green LED should turn off
    } else {
        digitalWrite(led3,LOW);
    }
    
        if (distance < 200) {  // This is where the LED On/Off happens
        digitalWrite(led2,HIGH); // When the Red condition is met, the Green LED should turn off
    } else {
        digitalWrite(led2,LOW);
    }
    
        if (distance < 100) {  // This is where the LED On/Off happens
        digitalWrite(led1,HIGH); // When the Red condition is met, the Green LED should turn off
    } else {
        digitalWrite(led1,LOW);
    }
    
    
    
    long diffDistance = distance - previousDistance;
    if (diffDistance < 0) diffDistance = diffDistance * -1;
    
    if (diffDistance > 5){
        previousDistance = distance;
        Serial.print(distance);
        Serial.println(" cm");
    }
}
