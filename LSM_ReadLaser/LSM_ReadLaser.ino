#define laserPin 7
#define greenPin 6
#define yellowPin 5
#define redPin 4
#define photoCellPin = 0;

long previousLaserDuration = 0;
int firstLoop = 1;
long currentStateInitMillis = 0;
int photoCellInput = 0;
int previousPhotoCellInput = 0;
int photoCellDiff = 0;

int debugMode = 0;

void setPinModes(){
    pinMode(laserPin, INPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    
}
void initSignal(){
    for (int i=1; i<4; i++){
        if(debugMode==1) { Serial.print("Init Signal Count: ");}
        if(debugMode==1) Serial.println(i);
        digitalWrite(greenPin, HIGH);  
        digitalWrite(yellowPin, HIGH);  
        digitalWrite(redPin, HIGH);  
        delay(1000);
        
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, LOW);  
        digitalWrite(redPin, LOW);          
        delay(1000);
    }
}


void setup() {
    Serial.begin (9600);
    if(debugMode==1) Serial.println("Initiating Sketch...");
    if(debugMode==1) Serial.println("Setting Pin Modes...");
    setPinModes();
    
    if(debugMode==1) Serial.println("Init Signal...");
    initSignal();
    
    if(debugMode==1) Serial.println("Setup Complete!");
}

long getLaserDurationFiveInARow(){
    long laserDuration_1 = pulseIn(laserPin, LOW, 5000);   
    long laserDuration_2 = pulseIn(laserPin, LOW, 5000);  
    long laserDuration_3 = pulseIn(laserPin, LOW, 5000);  
    long laserDuration_4 = pulseIn(laserPin, LOW, 5000);  
    long laserDuration_5 = pulseIn(laserPin, LOW, 5000);  
    
    if(debugMode==1) Serial.print("LD1: "); if(debugMode==1) Serial.println(laserDuration_1);
    if(debugMode==1) Serial.print("LD2: "); if(debugMode==1) Serial.println(laserDuration_2);
    if(debugMode==1) Serial.print("LD3: "); if(debugMode==1) Serial.println(laserDuration_3);
    if(debugMode==1) Serial.print("LD4: "); if(debugMode==1) Serial.println(laserDuration_4);
    if(debugMode==1) Serial.print("LD5: "); if(debugMode==1) Serial.println(laserDuration_5);    
    
    long laserDiff_1_2 = laserDuration_1 - laserDuration_2;
    long laserDiff_2_3 = laserDuration_2 - laserDuration_3;
    long laserDiff_3_4 = laserDuration_3 - laserDuration_4;
    long laserDiff_4_5 = laserDuration_4 - laserDuration_5;

    if (laserDiff_1_2 < 0) laserDiff_1_2 *= -1;
    if (laserDiff_2_3 < 0) laserDiff_2_3 *= -1;
    if (laserDiff_3_4 < 0) laserDiff_3_4 *= -1;
    if (laserDiff_4_5 < 0) laserDiff_4_5 *= -1;
    
    if(debugMode==1) Serial.print("LDD1: "); if(debugMode==1) Serial.println(laserDiff_1_2);
    if(debugMode==1) Serial.print("LDD2: "); if(debugMode==1) Serial.println(laserDiff_2_3);
    if(debugMode==1) Serial.print("LDD3: "); if(debugMode==1) Serial.println(laserDiff_3_4);
    if(debugMode==1) Serial.print("LDD4: "); if(debugMode==1) Serial.println(laserDiff_4_5);
    
    int diffOutOfSpec_Count =  0;
    long measuredDuration = 0;
    
    if (laserDiff_1_2 > 100) diffOutOfSpec_Count ++;
    else measuredDuration = laserDuration_1;
    
    if (laserDiff_2_3 > 100) diffOutOfSpec_Count ++;
    else measuredDuration = laserDuration_2;
    
    if (laserDiff_3_4 > 100) diffOutOfSpec_Count ++;
    else measuredDuration = laserDuration_3;
    
    if (laserDiff_4_5 > 100) diffOutOfSpec_Count ++;
      else measuredDuration = laserDuration_4;
      
    if(debugMode==1) Serial.print("Diff OS: "); if(debugMode==1) Serial.println(diffOutOfSpec_Count);
    if(debugMode==1) Serial.print("MD: "); if(debugMode==1) Serial.println(measuredDuration);      
  
    if(diffOutOfSpec_Count <= 1) {
        if(debugMode==1) Serial.println("Returned MD");
        return measuredDuration;
    } else {
        if(debugMode==1) Serial.println("Returned 0!");
        return 0;
    }
}

void setGreenLight_ON(){
    digitalWrite(greenPin, HIGH);  
    digitalWrite(redPin, LOW); 
        digitalWrite(yellowPin, LOW);  
}

void setGreenLight_OFF(){
    digitalWrite(greenPin, LOW);  
    digitalWrite(yellowPin, HIGH);  
}

void setRedLight_ON(){
    digitalWrite(redPin, HIGH);
}

void setRedLight_OFF(){
    digitalWrite(redPin, LOW);  
}

void loop() {
    if(firstLoop == 1){
      if(debugMode==1) Serial.println("Beginning Loop...");
    }
    long laserDuration, diffLaserDuration;

    laserDuration = getLaserDurationFiveInARow();    
    
    diffLaserDuration = laserDuration - previousLaserDuration;
    if (diffLaserDuration <0) diffLaserDuration = diffLaserDuration * -1;
    
    if(diffLaserDuration > 100) {
      if(debugMode==1) Serial.println("Status Changed!");
      previousLaserDuration = laserDuration;
      if(debugMode==1) Serial.print(micros());
      if(debugMode==1) Serial.print(" - Last Laser Duration: ");
      if(debugMode==1) Serial.println(laserDuration);
      
      currentStateInitMillis = millis();
      
    }

    if(laserDuration >1000 && laserDuration <4000){
        //Verify if it has been 1 second on laserDuration within range!
        if((millis() - currentStateInitMillis) > 1000) {
            setGreenLight_ON();
        } else {
            setGreenLight_OFF();
            setRedLight_OFF();
        }
    } else {
        //Verify if it has been 1 second on laserDuration within range!
        if((millis() - currentStateInitMillis) > 1000) {
            setRedLight_ON();
            setGreenLight_OFF();
        } else {
            setRedLight_OFF();
            setGreenLight_OFF();
        }        
    }
  
    photoCellInput = analogRead(0);
    photoCellDiff = photoCellInput - previousPhotoCellInput;
    if (photoCellDiff <0) photoCellDiff = photoCellDiff * -1;
    
    if(photoCellDiff > 10){
      previousPhotoCellInput = photoCellInput;
      if(debugMode==1) Serial.print(micros());
      if(debugMode==1) Serial.print(" - PhotoCell Reading Changed to: ");
      if(debugMode==1) Serial.println(photoCellInput);      
    }
    
   
    if(firstLoop == 1){
      if(debugMode==1) Serial.println("First Loop Complete!");
      firstLoop = 0;
    }    
    
    //delay(1000);
}
