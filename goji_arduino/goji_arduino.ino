// Includes
#include <dht11.h>

// Arduino Pin Defines
#define PHOTO_PIN   A0
#define TEMP_PIN    A1
#define DHT11_PIN   0

// Global Variables
dht11 DHT11;

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() {
  // send the value of analog input 0:
  Serial.println(analogRead(A0));
  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(2);
}
