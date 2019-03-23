#include "motors.h"

// HW serial port Serial1 pins RX D0 and TX D1 (only RX is realy used)

void setup()
{
 Serial.begin(9600); //This pipes to the serial monitor
 Serial1.begin(9600);
}

void loop()
{
  while (Serial1.available()) {
    Serial.print(char(Serial1.read()));
  }
}
