#include <EEPROM.h>

#define INTERVAL 180000 // 180000ms = 3 minutes in ms
#define MEMORY_SIZE 1024

int sensorPin = A0;    // select the input pin for the potentiometer
int analogValue = 0;   // variable to store the value coming from the sensor
int maxValue = 0;      // max value for the last 
unsigned long startTime = 0; // indicates the time when last write to EEPROM occured
int memOffset = 0;     // offset in EEPROM memory we're going to write to

int readButtonPin = 2;    // read button is on pin2

void setup() {
  pinMode(readButtonPin, INPUT);
  //Serial.begin(9600);  
  startTime = millis();
}

void printEEPROM()
{
  Serial.begin(9600);
  Serial.println("BEGIN MEMORY DUMP:");
  int value = 0;
  for (int i = 0; i < MEMORY_SIZE; i++) {
    value = EEPROM.read(i);
    Serial.println(value);
  }
  Serial.println("END MEMORY DUMP");
  Serial.end();
}

void loop() {
  if (digitalRead(readButtonPin) == HIGH) {
    printEEPROM();
  }
  
  // read the value from the sensor:
  analogValue = analogRead(sensorPin);
  if (analogValue > maxValue)
    maxValue = analogValue;

  if (millis() - startTime >= INTERVAL) {
    maxValue = maxValue >> 2; // Values from sensor seem to be in the range [0; 1023].
                              // Make sure they fit into 1 byte.
                              // Value of 255 means the byte is Unused.
    // just in case
    if (maxValue > 254)
      maxValue = 254;

    //Serial.println(maxValue);
    
    EEPROM.write(memOffset, maxValue);
    memOffset++;
    if (memOffset >= MEMORY_SIZE)
      memOffset = 0;
    maxValue = 0;
    startTime = millis();
  }
  // TODO: Go to sleep for a few seconds
}

