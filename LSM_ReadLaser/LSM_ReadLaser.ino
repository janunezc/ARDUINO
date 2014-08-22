#define rxPin     0
#define txPin     1

#define laserPin  2
#define greenPin  3
#define redPin    4

#define laserPin_b 5
#define greenPin_b 6
#define redPin_b   7

#define laserPin_b 8
#define greenPin_b 9
#define redPin_b   10

#define warningPin 11
#define alarmPin 12

#define blinkPin 13




#define photoCellPin = 0;

long previousLaserDuration = 0;
int firstLoop = 1;
long lastGreenMillisStamp = 0;
int photoCellInput = 0;
int previousPhotoCellInput = 0;
int photoCellDiff = 0;

int STATUS_STEADY_BEAM = 0; /*Beam detected steadily for 1 second or more*/
int STATUS_UNSTABLE_BEAM = 1; /*Beam detected for less than one second*/
int STATUS_ABSENT_BEAM = 2; /*Beam not detected for 1 second or more*/
int currentSensorStatus = 0;

long steadyBeamInitMillis = 0;
long absentBeamInitMillis = 0;

long readings_Count = 0;
long readingsInSpec_Count = 0;

long laserDurationSpec_min = 1000;
long laserDurationSpec_max = 4000;

String sensorStatus = "01-UNSTABLE_GREEN"; /*01-UNSTABLE_GREEN, 02-STABLE_GREEN, 03-RED*/

int debugMode = 0;

void setup() {
    Serial.begin (9600);
    if(debugMode==1) Serial.println("Initiating Sketch...");
    if(debugMode==1) Serial.println("Setting Pin Modes...");
    setPinModes();
    
    if(debugMode==1) Serial.println("Init Signal...");
    initSignal();
    
    if(debugMode==1) Serial.println("Setup Complete!");
}

void loop() {    
    if(firstLoop == 1 && debugMode==1) Serial.print("Beginning Loop...");
    if(debugMode==1) Serial.println(micros());
    
    determineSensorStatus();
    
    setSensorStatusPins();
      
    if(firstLoop == 1 && debugMode == 1) {
      Serial.println("First Loop Complete!");
      firstLoop = 0;
    }    
}

int determineSensorStatus(){
    long laserDuration, diffLaserDuration;
    
    laserDuration = getLaserDurationFiveInARow();    
    if(debugMode==1) Serial.print("Laser Duration: ");
    if(debugMode==1) Serial.println(laserDuration);
    
    if(isLaserDurationWithinSpec(laserDuration)){   
      absentBeamInitMillis = 0;
      if(steadyBeamInitMillis==0) steadyBeamInitMillis = millis();
      else if(millis()-steadyBeamInitMillis > 1000) {
        //BEAM IS STEADY
        currentSensorStatus =  STATUS_STEADY_BEAM;
      }
       
    } else {
      //BEAM IS NOT STEADY
      steadyBeamInitMillis = 0;
      currentSensorStatus = STATUS_UNSTABLE_BEAM;
      if(absentBeamInitMillis==0) absentBeamInitMillis = millis();
      else if (millis()-absentBeamInitMillis > 1000){
        currentSensorStatus =  STATUS_ABSENT_BEAM;
      } 
    } 
    
    return currentSensorStatus;
}

void setSensorStatusPins(){
    switch(currentSensorStatus){
       case 0: //STATUS_STEADY_BEAM
          setGreenLight_ON();
          setRedLight_OFF();      
          break;   
       case 1: //STATUS_UNSTABLE_BEAM
          setGreenLight_OFF();
          break;          
       case 2: //STATUS_ABSENT_BEAM
          setRedLight_ON();
          break;
    }
}

void setPinModes(){
    pinMode(laserPin, INPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    
}
void initSignal(){
    for (int i=1; i<4; i++){
        if(debugMode==1) { Serial.print("Init Signal Count: ");}
        if(debugMode==1) Serial.println(i);
        digitalWrite(greenPin, HIGH);  
        digitalWrite(blinkPin, HIGH);  
        digitalWrite(redPin, HIGH);  
        delay(1000);
        
        digitalWrite(greenPin, LOW);
        digitalWrite(blinkPin, LOW);  
        digitalWrite(redPin, LOW);          
        delay(1000);
    }
}





long getLaserDurationFiveInARow(){
    int laserDurationInSpec_Count = 0;

    long measuredDuration = 0;
    long laserDuration = 0;
    
    for(int i=0; i<10; i++){
       readings_Count ++;
       laserDuration = pulseIn(laserPin, LOW, 5000);
       
       if(isLaserDurationWithinSpec(laserDuration)) {
         laserDurationInSpec_Count ++; 
         readingsInSpec_Count ++;
         measuredDuration = laserDuration;
       }
       
       if(debugMode==1) {
         Serial.print("Laser Duration # ");
         Serial.print(i);Serial.print(": ");
         Serial.println(laserDuration);
                
       }
    }
    
 
     if(debugMode==1) {Serial.print("Measured Duration: "); Serial.println(measuredDuration); } 
   
     if(readings_Count==1000) {
         Serial.println("--------------------------------------------------");
         Serial.println("--------------------------------------------------");
         Serial.println("--------------------------------------------------");
         Serial.print("----- AVERAGE SAMPLES IN SPEC: ");
         Serial.print(readingsInSpec_Count);
         Serial.print(" OF ");
         Serial.print(readings_Count);
         readings_Count=0;
         readingsInSpec_Count=0;
     }
     
     if(laserDurationInSpec_Count >= 3) {
        if(debugMode==1) Serial.println("Returned MD");
        return measuredDuration;
    } else {
        if(debugMode==1) Serial.println("Returned 0");
        return 0;
    }
}

void setGreenLight_ON(){
    digitalWrite(greenPin, HIGH);  
}

void setGreenLight_OFF(){
    digitalWrite(greenPin, LOW);  
}

void setRedLight_ON(){
    digitalWrite(redPin, HIGH);
}

void setRedLight_OFF(){
    digitalWrite(redPin, LOW);  
}

boolean isLaserDurationWithinSpec(long duration){
  return duration > laserDurationSpec_min &&  duration < laserDurationSpec_max;
}


