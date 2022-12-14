#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32,16,2);
void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print("HELLO");
  lcd.setCursor(0,1);
  lcd.print("WORLD");
  lcd.clear();
  delay(1);
}
