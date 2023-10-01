#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
WiFiClient client;

#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT DHT11_INTERFACE(DHT_PIN, DHT_TYPE);
float temp = 0;
float hum = 0 ;

const char* ssid = "SPIKE";
const char* password = "Spike@1234";
const char* host = "dcs.glaitm.org"; 
const int httpsPort = 7080;

const char Thing[] = "Mohd_Ajlal-L-2215000600-thing";
const char Property1[] = "temp";
const char Property2[] = "hum";

void Put(String ThingName, String ThingProperty, String Value)
  {

    Serial.println(host);
  if (!client.connect(host, httpsPort)) 
 {
    Serial.println("connection failed");
    return;
  } else

 {
    Serial.println("Connected to ThingWorx.");
  }
  String url = "/Thingworx/Things/" + ThingName + "/Properties/" + ThingProperty; 
  Serial.print("requesting URL: ");
  Serial.println(url);

  String strPUTReqVal = "{\"" + ThingProperty + "\":\"" + Value + "\"}";  
  Serial.print("PUT Value: ");
  Serial.println(strPUTReqVal);

  client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "appKey: b7929102-dfec-49ab-ac69-f8f86211e9b1" + "\r\n" +
               "x-thingworx-session: false" + "\r\n" +
               "Accept: application/json" + "\r\n" +
               "Connection: close" + "\r\n" +
               "Content-Type: application/json" + "\r\n" +
               "Content-Length: " + String(strPUTReqVal.length()) + "\r\n\r\n" +
               strPUTReqVal + "\r\n\r\n");   

  while (client.connected()) 
{
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
}

void setup() 
{
 
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
 {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() 
{
  temp = DHT11_INTERFACE.readTemperature();
  hum = DHT11_INTERFACE.readHumidity();
 
  String strHum = String(hum); 
  String strTemp = String(temp); 
  Serial.print("Temp: ");
  Serial.println(strTemp);
  Serial.print("Hum: ");
  Serial.println(strHum);  

  Put(Thing,Property1,strTemp);  
  Put(Thing,Property2,strHum);

  
  delay(5000);
}
