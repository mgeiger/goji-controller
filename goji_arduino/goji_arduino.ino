//=========================================================
// Program:    goji_arduino.ino
// Author:     Matthew J. Geiger
// Version:    0.1
// Target:     n/a
// Date:       2014.01.04
// Time:       07:47
// Notes:
//             Serial I/O
//             DHT11 Library
// Reference:
//=========================================================


//===[ INCLUDE ]===========================================
#include <dht11.h>

//===[ CONSTANTS ]=========================================
// Debugging - 1:Enable; 0:Disable
#define DEBUG       1
// Arduino Pin Defines
#define PHOTO_PIN   A0
#define TEMP_PIN    A1
#define DHT11_PIN   0

//===[ VARIABLES ]=========================================
// Global Variables
dht11 DHT11;
int photoValue;

//===[ SETUP ]=============================================
void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  if (DEBUG) {
    Serial.println("GOJI Controller ");
    Serial.print("DHT11 LIBRARY VERSION: ");
    Serial.println(DHT11LIB_VERSION);
    Serial.println();
  }
}

//===[ LOOP ]==============================================
void loop() {
  // Check status of the DHT11 Sensor
  if (DEBUG) {
    int chk = DHT11.read(DHT11_PIN);
    Serial.print("Read sensor: ");
    switch (chk)
    {
      case DHTLIB_OK:
        Serial.println("OK"); 
	break;
      case DHTLIB_ERROR_CHECKSUM: 
	Serial.println("Checksum error"); 
	break;
      case DHTLIB_ERROR_TIMEOUT: 
	Serial.println("Time out error"); 
	break;
      default: 
	Serial.println("Unknown error"); 
	break;
    }
  }
  
  // send the value of analog input 0:
  Serial.println(analogRead(A0));
  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(2);
}
//=========================================================
