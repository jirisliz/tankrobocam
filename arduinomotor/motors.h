
#pragma once

#include <arduino.h>

// Robot motors pwm outputs
#define LMF 6  // Left Motor Forward
#define LMB 5  // Left Motor Backward
#define RMF 9  // Right Motor Forward
#define RMB 10 // Right Motor Backward

#ifdef __cplusplus
extern "C" {
#endif

void motorsInit();
void motorsStop();
void leftMotorForward(int aPwm);
void leftMotorBackward(int aPwm);
void rightMotorForward(int aPwm);
void rightMotorBackward(int aPwm);

#ifdef __cplusplus
}
#endif
