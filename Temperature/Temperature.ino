int val;
int tempPin = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(6, OUTPUT);
}
void loop()
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();

  Serial.print("TEMPRATURE = ");
  Serial.print(farh);
  Serial.print("*F");
  Serial.println();
  if (cel>300){
    digitalWrite(6, HIGH);
    digitalWrite(2, LOW);
    }
   else{
    digitalWrite(2, HIGH);
    digitalWrite(6, LOW);
    }
  }
