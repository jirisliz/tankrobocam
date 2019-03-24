#include "motors.h"

// HW serial port Serial1 pins RX D0 and TX D1 (only RX is realy used)

void setup()
{
  Serial.begin(9600); //This pipes to the serial monitor
  Serial1.begin(9600);

  motorsInit();
}

String cmd;

void loop()
{
  bool dataReceived = false;
  while (Serial.available()) {
    char c = Serial.read();
    cmd += c;
    dataReceived = true;
  }
  if (dataReceived)
  {
    parseCmd(cmd);
    cmd = "";
  }
}

void parseCmd(String cmd)
{
  if (cmd.startsWith("LF"))
  {
    leftMotorForward(100);
    Serial.print(cmd);
  }
  if (cmd.startsWith("LB"))
  {
    leftMotorBackward(100);
    Serial.print(cmd);
  }
  if (cmd.startsWith("RF"))
  {
    rightMotorForward(100);
    Serial.print(cmd);
  }
  if (cmd.startsWith("RB"))
  {
    rightMotorBackward(100);
    Serial.print(cmd);
  }
  if (cmd.startsWith("stop"))
  {
    motorsStop();
    Serial.print(cmd);
  }
  
}
