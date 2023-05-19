#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <ESP8266HTTPClient.h>
#define ACCEPT_TYPE "text/csv" //comma seperated value
WiFiClient client;
int relay1 = 2;

#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT DHT11_INTERFACE(DHT_PIN, DHT_TYPE);
float temp = 0;
float hum = 0 ;

const char* ssid = "GLA-CSED";
const char* password = "GLACAMPUS";
const char* host = "172.16.78.20"; 
const int httpsPort = 7080;

const char Thing[] = "mohdajlal-L-2215007018-thing";
const char Property1[] = "temp";
const char Property2[] = "hum";

const char appKey[]="8fc699b6-a935-4b25-86a7-c080ca113324";
const char get_Property1[] = "relay1";

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
               "appKey: 8fc699b6-a935-4b25-86a7-c080ca113324" + "\r\n" +
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
  String res1 = Get(Thing,get_Property1);  
 
  String strHum = String(hum); 
  String strTemp = String(temp); 
  Serial.print("Temp: ");
  Serial.println(strTemp);
  Serial.print("Hum: ");
  Serial.println(strHum); 
  Serial.println(res1);
  Serial.println(res1[11]); 

  Put(Thing,Property1,strTemp);  
  Put(Thing,Property2,strHum);
    if(res1[11]=='f')
  {
    digitalWrite(relay1,HIGH);
    Serial.println("relayoff");
  }
  else if(res1[11]=='t'){
    digitalWrite(relay1,LOW);
    Serial.println("relayon");
  }

}
String Get(String get_Thing, String get_Property1)
{              
        HTTPClient http;
        int httpCode = -1;
        String fullRequestURL = "http://" + String(host) +":"+ String(httpPort)+ "/Thingworx/Things/" 
                                + Thing + "/Properties/" + get_Property1 + "?appKey=" + appKey;

        Serial.println(fullRequestURL);
        http.begin(client, fullRequestURL);
        http.addHeader("Accept",ACCEPT_TYPE,false,false);        
        httpCode = http.GET();
        Serial.println(httpCode);

        String responses;
        if(httpCode > 0)        
        {             
           responses= http.getString(); 
             //Serial.println(responses);      
             //Serial.print(responses[9]);        
        }
        else         
        {
            Serial.println("[httpGetPropertry] failed, error: %s\n\n", http.errorToString(httpCode).c_str());
        }
        http.end();
        return responses; 

  
  delay(5000);
}
