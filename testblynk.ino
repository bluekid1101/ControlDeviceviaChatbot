#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char aut[] = "67f94a89b40b483d85e60a41584fc964";
char ssid[] = "Dinh";
char pass[] = "12121212";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(aut,ssid,pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
