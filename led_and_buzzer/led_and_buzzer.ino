// working on arduino uno

int LED = 3;
int buzzer = 7; 
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, LOW);
  delay(1000);
  tone(buzzer, 1000);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(1000);
  noTone(buzzer);
  delay(100);
}
