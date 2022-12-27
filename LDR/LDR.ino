// C++ code
//
int light;
void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  light = analogRead(A0);
  if(light<300){
    digitalWrite(2, HIGH);
    Serial.println(light);
  }
  else{
    digitalWrite(2, LOW);
    Serial.println(light);
  }
}
