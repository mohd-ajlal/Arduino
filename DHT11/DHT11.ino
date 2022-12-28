#include<TinyDHT.h>
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  delay(2000);
  float Hum = dht.readHumidity();
  float TempC = dht.readTemperature();
  float TempF = dht.readTemperature(true);

  Serial.println(Hum);
  Serial.println(TempC);
  Serial.println(TempF);
}
