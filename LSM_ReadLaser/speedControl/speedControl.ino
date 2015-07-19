/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int sensor1 = 2;
int sensor2 = 3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(sensor1, INPUT);     
  pinMode(sensor2, INPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  double time1 = millis();
  double time2 = millis();
  double sensorsDistance = 7;
  delay(2000);

  
  Serial.println("Waiting for Sensor 1...");
  while(digitalRead(sensor1)==0){}
  
  time1 = millis();

  Serial.println("Waiting for Sensor 2...");  
  while(digitalRead(sensor2)==0){}
  time2 = millis();
  
  double duration = time2 - time1;
  double speedPerMs = 1000*(sensorsDistance/duration);
  
  Serial.print("Duration was: ");
  Serial.println(duration);
  
  Serial.print("Speed was: ");
  Serial.print(speedPerMs);
  
  Serial.println(" cm/s");
    
  
}
