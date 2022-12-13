int Trigger = 2;
int Echo = 3; 
int distance = 0;
int duration = 0;
int inch = 0;
int ledPin1 = 4;
int ledPin2 = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop(){
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  duration = pulseIn(Echo, HIGH);
  distance = duration/2 * 0.0343;
  inch = distance * 0.393701;
  Serial.print(inch);
//  Serial.print(distance);
  Serial.println(" inch");
  if (inch<2)
  {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
  }
  else{
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin1, LOW);
  }
}
