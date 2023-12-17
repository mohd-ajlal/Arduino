//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//#include <IRremote.h>  // Make sure to include the correct version of IRremote (3.x or 4.x)
//#include <Keypad.h>
//
//const int irTransmitterPin = 8; // IR transmitter pin
//const int irReceiverPin = 9;    // IR receiver pin
//
//IRsend irSender;
//IRrecv irReceiver(irReceiverPin);
//decode_results results;
//
//
//LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows
//
//const byte ROWS = 4; //four rows
//const byte COLS = 4; //four columns
//char keys[ROWS][COLS] = {
//  {'1','2','3','A'},
//  {'4','5','6','B'},
//  {'7','8','9','C'},
//  {'*','0','#','D'}
//};
//byte rowPins[ROWS] = {40, 41, 42, 43}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {44, 45, 46, 47}; //connect to the column pinouts of the keypad
//Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//int read1=2;
//int read2=2;
//
//void setup() {
//  Serial.begin(9600);
//  irSender.begin(irTransmitterPin);  // The new IRsend object doesn't require a pin argument
//  irReceiver.enableIRIn(); // Start the IR receiver
//  lcd.begin(16, 2); // Initialize the LCD
//  lcd.backlight(); // Turn on the LCD backlight
//  pinMode(8, INPUT);
//pinMode(9, INPUT);
//}
//
//void loop() {
//  // Check for incoming IR data
//  if (irReceiver.decode(&results)) {
//    // Print the received code to the serial monitor
//    Serial.print("IR Received: 0x");
//    Serial.println(results.value, HEX);
//
//    // Display on the LCD
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("IR Code: ");
//    lcd.print(results.value, HEX);
//
//    irReceiver.resume(); // Receive the next value
//  }
//
//  // Check for keypad input
//  char key = keypad.getKey();
//  read1 = digitalRead(8);
//  read2 = digitalRead(9);
//  if (key) {
//    if(read1 == 0 && read2== 0){
//          Serial.print("KeyPad Value: ");
//    Serial.println(key);
//
//    // Transmit data via IR
//    irSender.sendNEC(results.value, 32);  // Use the received IR code instead of the keypad key
//
//    // Display on the LCD
//    lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print("Keypad: ");
//    lcd.print(key);
//      }
//  }
//  delay(1); // Adjust the delay based on your requirements
//}
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>  // Make sure to include the correct version of IRremote (3.x or 4.x)
#include <Keypad.h>

const int irTransmitterPin = 8; // IR transmitter pin
const int irReceiverPin = 9;    // IR receiver pin

IRsend irSender;
IRrecv irReceiver(irReceiverPin);
decode_results results;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'2','1','3','A'},
  {'5','4','6','B'},
  {'8','7','9','C'},
  {'0','*','#','D'}
};
byte rowPins[ROWS] = {40, 41, 42, 43}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44, 45, 46, 47}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  irSender.begin(irTransmitterPin);  // The new IRsend object doesn't require a pin argument
  irReceiver.enableIRIn(); // Start the IR receiver
  lcd.begin(16, 2); // Initialize the LCD
  lcd.backlight(); // Turn on the LCD backlight
}

void loop() {
  // Check for incoming IR data
  Serial.println("Hello");
  if (irReceiver.decode(&results)) {
    // Print the received code to the serial monitor
    Serial.print("IR Received: 0x");
    Serial.println(results.value, HEX);

    // Display on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IR Code: ");
    lcd.print(results.value, HEX);

    irReceiver.resume(); // Receive the next value
  }

  // Check for keypad input
  char key = keypad.getKey();
  if (key) {
    Serial.print("Keypad Input: ");
    Serial.println(key);

    // Transmit data via IR
    irSender.sendNEC(results.value, 32);  // Use the received IR code instead of the keypad key

    // Display on the LCD
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Keypad: ");
    lcd.print(key);
  }

  delay(1); // Adjust the delay based on your requirements
}
