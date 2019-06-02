#include <LiquidCrystal.h> //include LicquidCrystal Library

//variable for state
int state = 0;

//LCD panel set-up
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//I/O port setup
int REV_LIMITPORT = 11;
int LAUNCHPORT = 13;
int CLUTCHPORT = 12;


void setup() 
{

//Pin settings
pinMode (REV_LIMITPORT, OUTPUT); //Output to ECU Launch Control
pinMode (LAUNCHPORT, INPUT); //Launch Control switch
pinMode (CLUTCHPORT, INPUT); //Clutch switch
digitalWrite(LAUNCHPORT, HIGH); //Enable pull-up resistor
digitalWrite(CLUTCHPORT, HIGH); //Enable pull-up resistor

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

}

void loop()
{



while(state == 0){ //Idle mode (waiting for launch control switch to be ON)
  
      if (LAUNCHPORT == LOW)
      {
        state = state +1;
      }
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("state:IDLE");
          
          lcd.setCursor(0, 1);
          lcd.print(state);
          delay(5); 
      }



while (state == 1)
{ //Launch Control ready mode, waiting for clutch release (If the clutch is letgo before launching wait 4ms then turn off the switch and then back on)
 //What the rotary encoder will be doing
 //delays were added to debounce
       
        if (read_LCD_buttons() == btnUP)
        {
          l_delay = l_delay + 1;
          delay(150);
        }
        
        else if (read_LCD_buttons() == btnDOWN)
        {
          l_delay = l_delay - 1;
          delay(150);
        }
        
        //Setting the l_delay (launch delay)
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("state:LaunchRdy");
        
        lcd.setCursor(0,1);
        lcd.print(state);
       
        lcd.setCursor(7,1);
        lcd.print(l_delay);
        delay(5);
  
  
        //While btnRIGHT is held down keep Rev Limiter on
        while(LAUNCHPORT == LOW && CLUTCHPORT == LOW)
        {
            digitalWrite(REV_LIMITPORT, HIGH);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("state:LaunchON");
           
            lcd.setCursor(0, 1);
            lcd.print(state);
            
            lcd.setCursor(7,1);
            lcd.print(l_delay);
            delay(5);
      
      
            if (CLUTCHPORT == HIGH)
            { //Clutch released go SUSTAIN state
              state = state +1;
            }
        }
        
}



while (state == 2)
{ //Sustain mode
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:Sustain");
      
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(2);
  
      delay(1000); //this is where the l_delay is going to go (a number is just added to make sure it was in Sustain mode)
      state = state +1;
  
}



while (state ==3)
{ //Rev limiter OFF
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:OFF");
      
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(2);
    
    digitalWrite(REV_LIMITPORT, LOW);
   
    delay(1000);//delay added just to check that it went to OFF state
    state = state + 1;
}



while (state ==4)
{ //Wait for the Launch Control to be switched off to go back to ready
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("state:Wait");
      
      lcd.setCursor(0, 1);
      lcd.print(state);
      delay(2);
  
  if (LAUNCHPORT == HIGH){
    state = 0;
  }
}

}
