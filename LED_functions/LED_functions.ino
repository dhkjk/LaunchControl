#define LED1 2
#define LED2 7
#define LED3 11


void Blink_LED()
{
 for (int i = 0; i <2; i++){
     digitalWrite (LED1, HIGH);
     digitalWrite (LED2, HIGH);
     digitalWrite (LED3, HIGH);
     delay(100); //delay for 0.1 seconds
     digitalWrite (LED1, LOW);
     digitalWrite (LED2, LOW);
     digitalWrite (LED3, LOW);
     delay (100);
 }//blink for 0.6 seconds
}

void LED_ALL_OFF ()
{
  digitalWrite (LED1, LOW);
  digitalWrite (LED2, LOW);
  digitalWrite (LED3, LOW);
}

void LED1_ON()
{
  digitalWrite (LED1, HIGH);
}

void LED2_ON()
{
  digitalWrite (LED2, HIGH);
}

void LED3_ON()
{
  digitalWrite (LED3, HIGH);
}

void Walk_LED()
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


void setup() {
  // put your setup code here, to run once:
pinMode (LED1, OUTPUT);
pinMode (LED2, OUTPUT);
pinMode (LED3, OUTPUT);
}

//LED turns on when it outputs a HIGH

void loop() {
  // put your main code here, to run repeatedly:
  Blink_LED();
  delay(10);
  Walk_LED();
  delay(500);
  



}
