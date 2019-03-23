#ifndef __MOTORS__
#define __MOTORS__

// Robot motors pwm outputs
#define LMF 4  // Left Motor Forward
#define LMB 5  // Left Motor Backward
#define RMF 9  // Right Motor Forward
#define RMB 10 // Right Motor Backward

void motorsInit();

void leftMotorForward(int aPwm);
void leftMotorBackward(int aPwm);
void rightMotorForward(int aPwm);
void rightMotorBackward(int aPwm);

#endif
