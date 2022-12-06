// C++ code
//
int readva;
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);
}

void loop()
{
  readva = analogRead(A0);
  analogWrite(11, readva);  
}
