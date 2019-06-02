//#include <TimedAction.h> // include Protothreading
#include <LiquidCrystal.h> //include LicquidCrystal Library


//I/O port setup
#define LED1 1
#define LED2 2
#define LED3 3
#define Button 10
#define REV_LIMITPORT 11
#define CLUTCHPORT 12
#define LAUNCHPORT 13

int l_delay = 250;

//variable for state
int state = 0;//current state

//LCD panel set-up
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/*
//LED functions
void S_Blink() // Sustain Blink
{
    digitalWrite (LED1, HIGH);
    digitalWrite (LED2, HIGH);
    digitalWrite (LED3, HIGH);
    delay(300); //delay for 0.1 seconds
    digitalWrite (LED1, LOW);
    digitalWrite (LED2, LOW);
    digitalWrite (LED3, LOW);
    delay (300);
}

void Walk_LED() //Walking LED for Wait
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(10);
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);
  delay(10);
}

void LR_Blink() //Launch Ready state Blink
{
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW);
  delay(300);
}
*/

void setup() {
//Pin settings
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(Button, INPUT);
pinMode (REV_LIMITPORT, OUTPUT); //Output to ECU Launch Control
pinMode (CLUTCHPORT, INPUT); //Clutch switch
pinMode (LAUNCHPORT, INPUT); //Launch Control switch

//Enable pull-up resistor
digitalWrite(Button, HIGH);
digitalWrite(LAUNCHPORT, HIGH); 
digitalWrite(CLUTCHPORT, HIGH); 

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

}


void loop() {

while(state == 0){ //Idle mode (waiting for launch control switch to be ON)
  
  if (digitalRead(LAUNCHPORT) == LOW){
    state = state +1;
  }
  
  if (digitalRead(Button) == LOW){ //add 5 hundreth of a second to the delay for each button push
    l_delay = l_delay + 50;
    delay (10);

    if (l_delay >= 1000){
      l_delay = 0;
    }
  }

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(2);
  digitalWrite(LED3, LOW);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("state:IDLE");
  lcd.setCursor(0, 1);
  lcd.print(state);
  lcd.setCursor(7, 1);
  lcd.print("0.");
  lcd.setCursor(9, 1);
  lcd.print(l_delay/10);
  delay(7);
        
}

while (state == 1){ //Launch Control ready mode, waiting for clutch release (If the clutch is letgo before launching wait 4ms then turn off the switch and then back on)
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(2);
    digitalWrite(LED3, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("state:LaunchRdy");
    lcd.setCursor(0,1);
    lcd.print(state);
    lcd.setCursor(7,1);
    lcd.print(l_delay);
    delay(5);

    if (digitalRead(LAUNCHPORT) == HIGH)
      state = 0;
  
  while(digitalRead(CLUTCHPORT) == HIGH && digitalRead(LAUNCHPORT) == LOW){
      digitalWrite(REV_LIMITPORT, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:LaunchON");
      lcd.setCursor(0, 1);
      lcd.print(state);
      lcd.setCursor(7,1);
      lcd.print(l_delay);
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
      delay(l_delay); //delay is tenth of a second
      state = state +1;
      
      if (digitalRead(LAUNCHPORT) == HIGH) //
        state = 0;
  
}

while (state ==3){ //Rev limiter OFF
      digitalWrite(REV_LIMITPORT, LOW);
      delay(10);//delay added just to check that it went to OFF state
      state = state + 1;
}

while (state ==4){ //Wait for the Launch Control to be switched off to go back to ready
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      delay(2);
      digitalWrite(LED3, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:Wait");
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(2);
  while (state == 4){
    digitalWrite (LED3, LOW);
    delay(500);
    digitalWrite (LED3, HIGH);
    delay(500);
    
    if (digitalRead(LAUNCHPORT) == HIGH){
    state = 0;
    
  }
  
  }
}

}
