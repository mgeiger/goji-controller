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
//             Data Output: t0, t1, hum, phot, watr
//
// Reference:
//
// Circuit:
//             Analog Input
//             * A0 - MCP9700
//             * A1 - Photo Resistor
//             * A2 - Water Sensor
//             Digital Input
//             * 2 - DHT11
//             Digital Output
//             * 3 - Water Sensor Switch
//             * 4 - Fan PWM/Switch
//
//=========================================================


//===[ INCLUDE ]===========================================
#include <dht11.h>

//===[ CONSTANTS ]=========================================
// Debugging - 1:Enable; 0:Disable
#define DEBUG       0

// The number or readins for Array
const int numReadings = 10;

// Update Timer
const unsigned long refreshInterval = 5000UL;

//===[ PINS ]===============================================
// Arduino Pin Defines
#define TEMP_PIN    A0
#define PHTOTO_PIN  A1
#define WATER_PIN   A2
#define DHT11_PIN   2
#define WSWITCH_PIN 3
#define FAN_PIN     4

//===[ VARIABLES ]=========================================
// Global Variables
dht11 DHT11;
// int readings[numReadings];
// int index = 0;
// int total = 0;
// int average = 0;
// boolean filled = false;
// Sensor Values
int temp0 = 0;
int humid = 0;
int temp1 = 0;
int water = 0;
int photo = 0;
// Update Timer
unsigned long deltaTime = 0;

//===[ SETUP ]=============================================
void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  // if (DEBUG) {
  //   Serial.println("GOJI Controller ");
  //   Serial.print("DHT11 LIBRARY VERSION: ");
  //   Serial.println(DHT11LIB_VERSION);
  //   Serial.println();
  // }
}

//===[ LOOP ]==============================================
void loop() {
//    // Check status of the DHT11 Sensor
//  if (DEBUG) {
//    int chk = DHT11.read(DHT11_PIN);
//    Serial.print("Read sensor: ");
//    switch (chk)
//    {
//    case DHTLIB_OK:
//      Serial.println("OK"); 
//      break;
//    case DHTLIB_ERROR_CHECKSUM: 
//      Serial.println("Checksum error"); 
//      break;
//    case DHTLIB_ERROR_TIMEOUT: 
//      Serial.println("Time out error"); 
//      break;
//    default: 
//      Serial.println("Unknown error"); 
//      break;
//    }
//  }
//  // Get the DHT11 Values
//  float h = (float)DHT11.humidity;
//  float t1 = (float)DHT11.temperature;
//  
//  // Dummy values for photo and water
//  float p = 0.0;
//  float w = 0.0;
//
//  // Filter out the MCP9700 
//  total = total - readings[index];
//  readings[index] = analogRead(TEMP_PIN);
//  total = total + readings[index];
//  index = index + 1;
//  
//  if ((index == numReadings) && (!filled)) {
//     filled = true; 
//  }
//  
//  if (index >= numReadings) {
//    index = 0;
//  }
//    
//  average = total / numReadings;
//  
//  // The printed order will be:
//  // t0, t1, h, p, w
//  // Temperature 0, Temperature 1, Humidity, Photoresistor, Water Sensor
//  
//  if (!filled) {
//    Serial.print(readings[index], 4);
//  } else {
//    Serial.print(mcp2celcius(average), 4);
//  }
//  Serial.print(",");
//  Serial.print(t1, 4);
//  Serial.print(",");
//  Serial.print(h, 4);
//  Serial.print(",");
//  Serial.print(p, 4);
//  Serial.print(",");
//  Serial.println(w, 4);
  
  if ((millis() - deltaTime) >= refreshInterval) {
    deltaTime = millis();
    updateAllSensorValues();
  }
  
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

// This method will update all of the sensor values
void updateAllSensorValues() {
  temp1 = analogRead(TEMP_PIN);
  water = analogRead(WATER_PIN);
  photo = analogRead(PHOTO_PIN);
  updateDhtValues();
}

void updateDhtValues() {
  int chk = DHT11.read(DHT11_PIN);
    switch (chk) {
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

    float h = (float)DHT11.humidity;
    float t1 = (float)DHT11.temperature;
}
//=========================================================


