
/*
  Shift Register Sample
  
    Operates a Shift Register 74HC595N to light leds in order one by one.
 */
 
int blink_led_dp_8 = 8; /* BLUE: I use this LED to show a start and end point in the program. */
int _reset_10 = 10; /* WHITE: Performs a low-high-low to reset contents of the SR */
int shift_clock_11 = 11; /* YELLOW: Performs a LHL to shift contents of the register and fetch the data present in DATA SERIAL PIN*/
int latch_clock_12 = 12; /* GREEN: Performs a LHL to update Parallel Outputs with serial contents*/

int _output_enable_13 = 13; /*OPTIONAL: Normally pin 13  in the IC can be grounded.*/
int data_serial_14_9 = 9; /*ORANGE: H or L should be present in the pin 14 of the IC when Shift-Clock is actuated. */

int signalDelay = 10; /*DELAY BETWEEN SIGNAL CHANGES TO GIVE THE CHIP TIME TO REACT */

void setup() {    

  /*SET PINS AS OUTPUTS */
  pinMode(blink_led_dp_8, OUTPUT);
  pinMode(_reset_10 , OUTPUT); /*LOW DOES RESET, HIGH ENABLES*/    
  pinMode(shift_clock_11 , OUTPUT);  /*HIGH SHIFTS*/
  pinMode(latch_clock_12 , OUTPUT); /*HIGH Stores*/
  pinMode(data_serial_14_9 , OUTPUT); /*PUT 1 or 0 just before setting latch_clock_12 to HIGH*/
  pinMode(_output_enable_13 , OUTPUT); /*HIGH enables*/
  
  /*LETS BEGIN BY PUTTING CONTROL SIGNALS IN LOW*/  
  shutControlPinsDown();

  /*FIRST OF ALL - RESET THE CHIP */
  resetRegister();  
  
  /*INDICATES ROUTINE START*/
  digitalWrite(blink_led_dp_8, HIGH); delay(100);
  digitalWrite(blink_led_dp_8, LOW); delay(1000);
  digitalWrite(blink_led_dp_8, HIGH); delay(100);
  digitalWrite(blink_led_dp_8, LOW); delay(1000);
  digitalWrite(blink_led_dp_8, HIGH); delay(100);
  digitalWrite(blink_led_dp_8, LOW); delay(1000);
  
  injectBit();//1
  injectBit();//2
  injectBit();//3
  injectBit();//4
  injectBit();//5
  injectBit();//6
  injectBit();//7
  injectBit();//8
  injectBit();//9

  /*LETS FINISH PUTTING DOWN ALL CONTROL PINS*/
  shutControlPinsDown();
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(blink_led_dp_8, LOW); delay(50);
  digitalWrite(blink_led_dp_8, HIGH); delay(50);
}

void injectBit(){
  
   /*PLACE A HIGH in the data bit. */
  setDataBitHIGH();
  
  /*SHIFT CLOCK FOR SHIFT*/
  doShift();
  
  /*STORE IT*/    
  doLatch();    
 
}

void shutControlPinsDown(){
  digitalWrite(_reset_10, LOW);
  digitalWrite(shift_clock_11, LOW);
  digitalWrite(latch_clock_12, LOW); 
  digitalWrite(_output_enable_13, LOW);
  digitalWrite(data_serial_14_9, LOW);
  delay(1000);  
}

void resetRegister(){
  digitalWrite(_reset_10, HIGH); delay (signalDelay);/*END RESET*/
  digitalWrite(_reset_10, LOW); delay(signalDelay);
  digitalWrite(_reset_10, HIGH); delay (signalDelay);/*END RESET*/
  
  doLatch();
}

void setDataBitHIGH(){
  digitalWrite(data_serial_14_9, HIGH);  delay(signalDelay); 
}

void doShift(){
   digitalWrite(shift_clock_11, LOW); delay(signalDelay); 
   digitalWrite(shift_clock_11, HIGH); delay(signalDelay);   
   digitalWrite(shift_clock_11, LOW); delay(signalDelay); 
}

void doLatch(){
   digitalWrite(latch_clock_12, LOW); delay(signalDelay); 
   digitalWrite(latch_clock_12, HIGH); delay(signalDelay);   
   digitalWrite(latch_clock_12, LOW); delay(signalDelay);   
}

void enableOutput(){
  digitalWrite(_output_enable_13, LOW); delay(signalDelay); 
}
