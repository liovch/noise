#include <EEPROM.h>

#define MEMORY_SIZE 1024

void setup()
{
  // Note: The EEPROM memory has a specified life of 100,000 write/erase cycles.
  // Initialize EEPROM to 255
  for (int i = 0; i < MEMORY_SIZE; i++)
    EEPROM.write(i, 255);
}

void loop() {
}
