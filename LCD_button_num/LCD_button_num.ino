#include <LiquidCrystal.h>

// No button press >1000
// BtnR < 50
// BtnL < 195
// BtnD < 380
// BtnU < 555
// BtnSelect <790

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key = 0;
int adc_key_in = 0;

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  return adc_key_in;
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Button number is");

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd_key = read_LCD_buttons();
  lcd.print (lcd_key);
  delay(5);

}
