//By: Dae Kim
//Second arduino file to test on car with encoder
#include <LiquidCrystal.h> //include LicquidCrystal Library

//variable for state
int state = 0;//current state
//int l_delay = encoder0Pos;//The amount of launch control delay


//LCD panel set-up
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//I/O port setup
const int REV_LIMITPORT = 11;
const int LAUNCHPORT = 13;
const int CLUTCHPORT = 12;


//encoder port setup
#define encoder0PinA  2
#define encoder0PinB  3
volatile unsigned int encoder0Pos = 0;

/*
void doEncoder() {
   If pinA and pinB are both high or both low, it is spinning
     forward. If they're different, it's going backward.

     For more information on speeding up this process, see
     [Reference/PortManipulation], specifically the PIND register.
  detachinterrupt(0);
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    encoder0Pos++;
    attachInterrupt(0, doEncoder, CHANGE);
  } else {
    encoder0Pos--;
    attachInterrupt(0, doEncoder, CHANGE);
  }
}
*/


// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result

 // For V1.0 comment the other threshold and use the one below:

 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   



 return btnNONE;  // when all others fail, return this...
}





void setup() {
//encoder setup
//pinMode(encoder0PinA, INPUT);
//digitalWrite(encoder0PinA, HIGH);       // turn on pull-up resistor
//pinMode(encoder0PinB, INPUT);
//digitalWrite(encoder0PinB, HIGH);       // turn on pull-up resistor
//attachInterrupt(0, doEncoder, CHANGE);  // encoder pin on interrupt 0 = pin 2

//Pin settings
pinMode (REV_LIMITPORT, OUTPUT); //Output to ECU Launch Control
pinMode (LAUNCHPORT, INPUT); //Launch Control switch
pinMode (CLUTCHPORT, INPUT); //Clutch switch
digitalWrite(LAUNCHPORT, HIGH); //Enable pull-up resistor
digitalWrite(CLUTCHPORT, HIGH); //Enable pull-up resistor

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

}

void loop() {

while(state == 0){ //Idle mode (waiting for launch control switch to be ON)
  if (digitalRead(LAUNCHPORT) == LOW){
    state = state +1;
  }
  
       if (read_LCD_buttons() == btnUP)
    {
      encoder0Pos = encoder0Pos + 1;
      delay(150);
    }
    else if (read_LCD_buttons() == btnDOWN)
    {
      encoder0Pos = encoder0Pos - 1;
      delay(150);
    }
    
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:IDLE");
      lcd.setCursor(0, 1);
      lcd.print(state);
      lcd.setCursor(7, 1);
      lcd.print(encoder0Pos);
      delay(7);
    }
        
}

while (state == 1){ //Launch Control ready mode, waiting for clutch release (If the clutch is letgo before launching wait 4ms then turn off the switch and then back on)
 
   //What the rotary encoder will be doing
   //delays were added to debounce
    if (read_LCD_buttons() == btnUP)
    {
      encoder0Pos = encoder0Pos + 1;
      delay(150);
    }
    else if (read_LCD_buttons() == btnDOWN)
    {
      encoder0Pos = encoder0Pos - 1;
      delay(150);
    }
  
    
    //Setting the l_delay (launch delay)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("state:LaunchRdy");
    lcd.setCursor(0,1);
    lcd.print(state);
    lcd.setCursor(7,1);
    lcd.print(encoder0Pos);
    delay(5);

    if (digitalRead(LAUNCHPORT) == HIGH)
      state = 0;
  
  //While btnRIGHT is held down keep Rev Limiter on
  while(digitalRead(CLUTCHPORT) == HIGH && digitalRead(LAUNCHPORT) == LOW){
      digitalWrite(REV_LIMITPORT, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:LaunchON");
      lcd.setCursor(0, 1);
      lcd.print(state);
      lcd.setCursor(7,1);
      lcd.print(encoder0Pos);
      delay(5);

       if (digitalRead(LAUNCHPORT) == HIGH)
        state = 0;

      if (digitalRead(CLUTCHPORT) == LOW){
        state = state +1;
      }
  }
  
}

while (state == 2){ //Sustain mode
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:Sustain");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(encoder0Pos * 100); //delay is tenth of a second
      state = state +1;
      if (digitalRead(LAUNCHPORT) == HIGH)
        state = 0;
  
}

while (state ==3){ //Rev limiter OFF
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:OFF");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(2);
      digitalWrite(REV_LIMITPORT, LOW);
      delay(1000);//delay added just to check that it went to OFF state
      state = state + 1;
      if (digitalRead(LAUNCHPORT) == HIGH)
        state = 0;
}

while (state ==4){ //Wait for the Launch Control to be switched off to go back to ready
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:Wait");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(2);
  
  if (digitalRead(LAUNCHPORT) == HIGH){
    state = 0;
  }
}

}
