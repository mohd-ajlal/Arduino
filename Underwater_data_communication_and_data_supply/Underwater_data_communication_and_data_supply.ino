#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <Keypad.h>

const int irTransmitterPin = 2; // IR transmitter pin
const int irReceiverPin = 3;    // IR receiver pin

IRsend irSender;
IRrecv irReceiver(irReceiverPin);
decode_results results;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 11, 10}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  irSender.begin(irTransmitterPin); // Specify the IR transmitter pin
  irReceiver.enableIRIn();          // Start the IR receiver
  lcd.begin(16, 2);                  // Initialize the LCD
  lcd.backlight();                   // Turn on the LCD backlight
}

void loop() {
  // Check for incoming IR data
  if (irReceiver.decode(&results)) {
    // Print the received code to the serial monitor
    Serial.print("IR Received: 0x");
    Serial.println(results.value, HEX);

    // Display on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IR Code: ");
    lcd.print(results.value, HEX);

    irReceiver.resume();  // Receive the next value
  }

  // Check for keypad input
  char key = keypad.getKey();
  if (key) {
    Serial.print("Keypad Input: ");
    Serial.println(key);

    // Transmit data via IR
    irSender.sendNEC(static_cast<uint32_t>(key), 32);

    // Display on the LCD
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Keypad: ");
    lcd.print(key);
  }

  delay(1); // Adjust the delay based on your requirements
}
