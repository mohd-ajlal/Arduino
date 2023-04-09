int LED_R=13;
int MY_IR=7;
int MY_RELAY=10;
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  pinMode(LED_R,OUTPUT);
  pinMode(MY_IR,INPUT);
  pinMode(MY_RELAY,OUTPUT);
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(500);
  display.clearDisplay(); 
}

void loop() {
  if(digitalRead(MY_IR)==LOW){
    digitalWrite(LED_R,LOW);
    digitalWrite(MY_RELAY,HIGH);
     display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Contactless");
    display.setCursor(20, 30);
    display.println("");
    display.println("DoorBell");
    display.display();
    delay(500);
    display.clearDisplay();
 
    }
  else {
    digitalWrite(LED_R,HIGH);
    digitalWrite(MY_RELAY,LOW);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Please Wait....");
    display.display();
    delay(500);
    display.clearDisplay();
 
    }  

}
