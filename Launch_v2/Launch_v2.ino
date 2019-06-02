int state = 0;

void setup() {
  // put your setup code here, to run once:
pinMode (13, OUTPUT);   //Output to click the relay
pinMode (9, INPUT);     //Input for Clutch sensor
pinMode (8, INPUT);     //Input for Launch Control switch
digitalWrite(8, HIGH);  //Pull-up resistor on
digitalWrite(9, HIGH);  //Pull-up resistor on

}

void loop() {
  // put your main code here, to run repeatedly:

while (state == 0){     //Ready state for Launch
        while (digitalRead(8)== LOW && digitalRead(9) == LOW)
      {
        digitalWrite(13, HIGH);
          
      }
    delay(2); //Delay for 2 ms
    state = state + 1;
}

while (state ==1){ //Turn off the launch control
      
       digitalWrite(13, LOW);
       delay(1);
       state = state +1;
}

while (state == 2){           //If the switch is turned off, set the state back to ready
  if (digitalRead(8) == HIGH){
    state = 0;
  }

}
}
