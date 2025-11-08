#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// 引入必要的库
#include "lib/lib/lib.h"
#include "lib/deploy/deploy.h"

class MotorControl {
public:
  MotorControl();

  bool stepper_x(double distance, int speed, int step_length);
  bool stepper_y(double distance, int speed, int step_length);
  bool stepper_z(double distance, int speed, int step_length);

private:

  
};

#endif