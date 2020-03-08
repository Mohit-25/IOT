#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHT_pin 14

DHT dht(DHT_pin, DHTTYPE);

const char* ssid = "vivo 1727";
const char* password = "12345678";

void setup () {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  delay(2000);
  dht.begin();
  delay(2000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED)    //Check WiFi connection status
  {
    HTTPClient http;                    //Declare an object of class HTTPClient

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print("temperature = ");
    Serial.print(t);
    Serial.print("C  ");
    Serial.print("humidity = ");
    Serial.print(h);
    Serial.println("%  ");

    delay(1000);

    //String URL for GET request
    String url = "http://mohitd.eu-gb.mybluemix.net";
    String api = "/data";
    url += api;
    String param1 = "?temp=" + String(t);
    url += param1;
    String param2 = "&hum=" + String(h);
    url += param2;
    Serial.print("HTTP GET : ");
    Serial.println(url);

    http.begin(url);                              //Specify request destination

    int httpCode = http.GET();                    //Send the request

    if (httpCode > 0) {                           //Check the returning code
      String payload = http.getString();          //Get the request response payload
      Serial.println(payload);                    //Print the response payload
    }

    http.end();   //Close connection
  }

  delay(10000);    //Send a request every 30 seconds
}
