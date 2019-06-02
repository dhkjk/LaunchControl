//By: Dae Kim
#include <LiquidCrystal.h> //include LicquidCrystal Library

//variable for state
int state = 0;

//LCD panel set-up
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//I/O port setup
int REV_LIMITPORT = 11;
int LAUNCHPORT = 13;
int CLUTCHPORT = 12;


void setup() {
//Pin settings
pinMode (REV_LIMITPORT, OUTPUT); //Output to ECU Launch Control
pinMode (LAUNCHPORT, INPUT); //Launch Control switch
pinMode (CLUTCHPORT, INPUT); //Clutch switch
//digitalWrite(LAUNCHPORT, HIGH); //Enable pull-up resistor
//digitalWrite(CLUTCHPORT, HIGH); //Enable pull-up resistor

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

}

void loop() {

while(state == 0){ //Idle mode (waiting for launch control switch to be ON)

  while (digitalRead(LAUNCHPORT) == HIGH)
  {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("flip launch switch");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(7);
  }
  
  
  while (digitalRead(LAUNCHPORT) == LOW){
    state = state +1;
  }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:IDLE");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(7);
  

  
}

while (state == 1){ //Launch Control ready mode, waiting for clutch release (If the clutch is letgo before launching wait 4ms then turn off the switch and then back on)
  while(digitalRead(CLUTCHPORT) != LOW && digitalRead(LAUNCHPORT) == LOW){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:LaunchRdy");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(5);
  }//Loop for when clutch isn't intiated.

  
 while(digitalRead(CLUTCHPORT) == LOW && digitalRead(LAUNCHPORT) == LOW){
    digitalWrite(REV_LIMITPORT, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:LaunchON");
      lcd.setCursor(0, 1);
      lcd.print(state);
  }  //Clutch switch intiated and launch control switch is turned on

  state = state +1;
  
}

while (state == 2){ //Sustain mode
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:Sustain");
      lcd.setCursor(0, 1);
      lcd.print(state);
  delay(1000); //keep rev limiter on for 4ms more
  state = state +1;
  
}

while (state ==3){ //Rev limiter OFF
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:OFF");
      lcd.setCursor(0, 1);
      lcd.print(state);
  digitalWrite(REV_LIMITPORT, LOW);
    delay(1000);
  state = state + 1;
}

while (state ==4){ //Wait for the Launch Control to be switched off to go back to ready
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:Wait");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(5);
  
  if (digitalRead(LAUNCHPORT) == HIGH){
    state = 0;
  }
}

}
