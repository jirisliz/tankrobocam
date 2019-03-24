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
  while (Serial.available()) {
    char c = Serial.read();
    cmd += c;
    if (c == '\n')
    {
      parseCmd(cmd);
      cmd = "";
    }
  }

}

/**
   Parses and executes command in form <command>-<value>#
*/
void parseCmd(String cmd)
{
  String strCmd;
  String strValue;
  if(cmd.indexOf("-") > 0)
  {
    strCmd = cmd.substring(0, cmd.indexOf("-"));
    strValue = cmd.substring(cmd.indexOf("-") + 1, cmd.indexOf("\n"));
  }
  else if(cmd.indexOf("\n") > 0)
  {
    strCmd = cmd.substring(0, cmd.indexOf("#"));
  }
  else return;
  
  Serial.println("strCmd: " + strCmd);
  Serial.println("strValue: " + strValue);

  
    if (strCmd.indexOf("LF") >= 0)
    {
    leftMotorForward(strValue.toInt());
    Serial.print(cmd);
    }
    if (strCmd.indexOf("LB") >= 0)
    {
    leftMotorBackward(strValue.toInt());
    Serial.print(cmd);
    }
    if (strCmd.indexOf("RF") >= 0)
    {
    rightMotorForward(strValue.toInt());
    Serial.print(cmd);
    }
    if (strCmd.indexOf("RB") >= 0)
    {
    rightMotorBackward(strValue.toInt());
    Serial.print(cmd);
    }
    if (strCmd.indexOf("stop") >= 0)
    {
    motorsStop();
    Serial.print(cmd);
    }
  

}
