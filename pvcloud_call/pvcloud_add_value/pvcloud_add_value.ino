#include <string.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int readPin = 12;
int prevVal = 0;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  pinMode(readPin, INPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  int val = digitalRead(readPin);
  if(prevVal != val) {
    prevVal = val;
    sendValueToCloud("1025", "SENSOR_12", "DIGITAL", val, "2014-11-27+10:07");   
    sendValueToCloud("1025", "SENSOR_12", "DIGITAL", "TEST123", "2014-11-27+10:07");   
  }

}
/*
void sendValueToCloud(float value){
   String strValue = String(value);
   String nodeCommand = "node /home/root/nodejs_projects/marie/pvcloud_add_value.js device_id=2047 value_label=analog value=" + strValue + " value_type=analog captured_datetime=2014-11-27+10:07";
   system(nodeCommand);
}
*/

void sendValueToCloud(char * deviceID, char * valueLabel, char * valueType, int value, char * capturedDatetime){
  //http://www.instructables.com/id/Converting-integer-to-character/
   char buffer [4];
   String strValue = String(value);
   strValue.toCharArray(buffer,4);
   
   char * valueX = buffer;
    
   char * nodeCommand = "node /home/root/nodejs_projects/marie/pvcloud_add_value.js";
   
   char dest[1000];
   strcpy(dest, nodeCommand);
   strcat(dest, " device_id=");
   strcat(dest, deviceID);
   
   strcat(dest, " value_label=");
   strcat(dest, valueLabel);   
   
   strcat(dest, " value_type_code=");
   strcat(dest, valueType);      
   
   strcat(dest, " value=");
   strcat(dest, valueX);  
  
   strcat(dest, " captured_datetime=");
   strcat(dest, capturedDatetime);  
   
   const char * nc = dest ;
   
   char * c = nodeCommand;

   Serial.println(nc);
   
   system (nc);

}

void sendValueToCloud(char * deviceID, char * valueLabel, char * valueType, String value, char * capturedDatetime){
   char buffer [10];
   value.toCharArray(buffer,10);
   
   char * valueX = buffer;
    
   char * nodeCommand = "node /home/root/nodejs_projects/marie/pvcloud_add_value.js";
   
   char dest[1000];
   strcpy(dest, nodeCommand);
   strcat(dest, " device_id=");
   strcat(dest, deviceID);
   
   strcat(dest, " value_label=");
   strcat(dest, valueLabel);   
   
   strcat(dest, " value_type_code=");
   strcat(dest, valueType);      
   
   strcat(dest, " value=");
   strcat(dest, valueX);  
  
   strcat(dest, " captured_datetime=");
   strcat(dest, capturedDatetime);  
   
   const char * nc = dest ;
   
   char * c = nodeCommand;

   Serial.println(nodeCommand);
   
   system (nc);

}
