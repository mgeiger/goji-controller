//=========================================================
// Program:    goji_arduino.ino
// Author:     Matthew J. Geiger
// Version:    0.1
// Target:     n/a
// Date:       2014.01.18
// Time:       15:08
// Notes:
//             Serial I/O
//             DHT11 Library
// Reference:
//
// Circuit:
//             Analog Input
//             * 0 - MCP9700
//             Digital Input
//             * 0 - DHT11
//=========================================================


//===[ INCLUDE ]===========================================
#include <dht11.h>

//===[ CONSTANTS ]=========================================
// Debugging - 1:Enable; 0:Disable
#define DEBUG       0

// The number or readins for Array
const int numReadings = 10;

//===[ PINS ]===============================================
// Arduino Pin Defines
#define TEMP_PIN  A0
#define DHT11_PIN 2

//===[ VARIABLES ]=========================================
// Global Variables
dht11 DHT11;
int readings[numReadings];
int index = 0;
int total = 0;
int average = 0;

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
  // Get the DHT11 Values
  float h = (float)DHT11.humidity;
  float t1 = (float)DHT11.temperature;

  // Filter out the MCP9700 
  total = total - readings[index];
  readings[index] = analogRead(TEMP_PIN);
  total = total + readings[index];
  index = index + 1;
  
  if (index >= numReadings) {
    index = 0;
  }
    
  average = total / numReadings;
  
  Serial.print(mcp2celcius(average), 4);
  Serial.print(",");
  Serial.print(t1, 4);
  Serial.print(",");
  Serial.println(h, 4);

  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(10);
}

//===[ SUBROUTINES ]=======================================
// Takes in the MCP9700 Analog read value and returns the 
// celcius value
float mcp2celcius(int mcp) {
  float temp = ((mcp * 5) / 1024.0);
  temp = (temp - 0.5);
  temp = (temp / 0.01);
  return temp;
}
//=========================================================


