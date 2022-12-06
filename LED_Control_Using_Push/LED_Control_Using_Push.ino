void setup()
{
  Serial.begin(9600);
  pinMode(11, INPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  if(digitalRead(11)==1)
  {
    digitalWrite(8, HIGH);
  }
  else
  {
    digitalWrite(8, LOW);
  }
}
