/*
 * PIR and DHT and Ultrasonic sensor tester for serial monitor
 */
#include "DHT.h"

#define DHTPIN 3 
#define DHTTYPE DHT22

#define PIR 2 

//#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
//#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

DHT dht(DHTPIN, DHTTYPE);

int pirState, counter = 0;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

void setup() {
  pinMode(PIR, INPUT);     // declare sensor as input
 
  Serial.begin(9600);

  Serial.println("Sensor interface test!");

  dht.begin();
}
 
void loop(){

   delay(2000);
   
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

   // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.println(F("Humidity: "));
  Serial.println(h);
  Serial.println(F("Temperature: "));
  Serial.println(t);
  //Serial.print(F("°C "));

   delay(2000);

   PiRSensor();
  
}

void PiRSensor() {
 val = digitalRead(PIR);  // read input value
  if (val == HIGH) {
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = 1;
      Serial.println(pirState);
    }
  } else {
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = 0;
      Serial.println(pirState);
  }
}
}
