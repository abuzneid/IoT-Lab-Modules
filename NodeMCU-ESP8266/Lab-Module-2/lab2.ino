//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN  5      //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);
BlynkTimer timer;


char auth[] = "53573ff15xxxxxxxxxxxxxxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxxx";
char pass[] = "xxxxxx";


void readSensor() {
  float h = dht.readHumidity(); // read humidity 
  float t = dht.readTemperature(); // read Temperature 
  Serial.println(t);
  delay(100);
  Serial.println(h);



  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    Blynk.virtualWrite(V0, t); // virtual pin
    Blynk.virtualWrite(V1, h); // virtual pin
}


void setup() {
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  dht.begin();
  timer.setInterval(3000, readSensor);     //Read every 3 secs
}


void loop() {
  Blynk.run();
  timer.run();
}
