#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int IRSensor1 = 7;
int IRSensor2 = 8;
int RELAY = 13; 
int count = 0;

void setup()
{
  lcd.begin();

 // Turn on the blacklight and print a message.
  lcd.backlight();
  pinMode(IRSensor1, INPUT); 
  pinMode(IRSensor2, INPUT);
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  delay(100);
  int sensorStatus1 = !digitalRead(IRSensor1); 
  int sensorStatus2 = !digitalRead(IRSensor2);
  if (sensorStatus1){
      // Serial.println("initial1");
      while (!sensorStatus2){
      sensorStatus2 = !digitalRead(IRSensor2);
        delay(100);
      }
      count++;
          lcd.clear();                 
    lcd.setCursor(0, 0);         
    lcd.print("PERSON IN: ");        
    lcd.setCursor(0, 1);       
    lcd.print(count); 
    delay(100);
  }
    else if(sensorStatus2){
    // Serial.println("initial2");
      while (!sensorStatus1){
      sensorStatus1 = !digitalRead(IRSensor1);
      // Serial.println("initial2-");
        delay(100);
      }
      count--;
      lcd.clear();                 
      lcd.setCursor(0, 0);         
      lcd.print("PERSON IN: ");        
      lcd.setCursor(0, 1);       
      lcd.print(count); 
      delay(100);
    
    }
    Serial.print("count: ");
    Serial.println(count); 
//    lcd.clear();                 
//    lcd.setCursor(0, 0);         
//    lcd.print("PERSON IN: ");        
//    lcd.setCursor(0, 1);       
//    lcd.print(count); 
//    delay(2000);



  
//  if (sensorStatus1 == 1 && sensorStatus2 == 1) 
//  {
//    // if the pin is high turn off the onboard Led
//    digitalWrite(RELAY, HIGH);
//    count += 1;
//    Serial.println(count); 
//    lcd.clear();                 
//    lcd.setCursor(0, 0);         
//    lcd.print("PERSON IN: ");        
//    lcd.setCursor(0, 1);       
//    lcd.print(count); 
//    delay(2000);
//  }
//  else  {
//    digitalWrite(RELAY, LOW);
//    count += 0;// LED LOW
//    Serial.println(count); 
//    lcd.clear();               
//    lcd.setCursor(0, 0);        
//    lcd.print("PERSON IN: ");     
//    lcd.setCursor(0, 1);         
//    lcd.print(count); 
//    delay(2000);
//  }

int sensor1Pin = A0;
if (sesor1 == HIGH)
{
  
  while(digitalRead(sensor1Pin));
  delay(10);
  while(!digitalRead(sensor2Pin))
  { count++;
  while(digitalRead(sensor2Pin));
  break
    }
  
}
  
  
  }

}
