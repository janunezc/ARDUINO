/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  Serial.println("READY!");
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("BLINK LOOP");
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  Serial.println("Doing nodejs system call...");
  system ( "node /home/root/pvcloud_api.js action='add_value' value='ONE BLINK OCCURRED' value_type='ANY_TYPE_IS_FINE' value_label='ANY LABEL WORKS' captured_datetime='2000-01-01+10:23'");
  Serial.println("System Call complete");
}
