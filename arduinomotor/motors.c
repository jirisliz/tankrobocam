
#include "motors.h"

void motorsInit()
{
  pinMode(LMF, OUTPUT);
  pinMode(LMB, OUTPUT);
  pinMode(RMF, OUTPUT);
  pinMode(RMB, OUTPUT);
  motorsStop();
}

void motorsStop()
{
  digitalWrite(LMF, LOW);
  digitalWrite(LMB, LOW);
  digitalWrite(RMF, LOW);
  digitalWrite(RMB, LOW);
}

void leftMotorForward(int aPwm)
{
  analogWrite(LMF, aPwm);
  digitalWrite(LMB, LOW);
}

void leftMotorBackward(int aPwm)
{
  analogWrite(LMB, aPwm);
  digitalWrite(LMF, LOW);
}

void rightMotorForward(int aPwm)
{
  analogWrite(RMF, aPwm);
  digitalWrite(RMB, LOW);
}

void rightMotorBackward(int aPwm)
{
  analogWrite(RMB, aPwm);
  digitalWrite(RMF, LOW);
}
