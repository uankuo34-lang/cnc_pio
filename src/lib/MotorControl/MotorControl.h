#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// 引入必要的库
#include "lib/lib/lib.h"
#include "lib/deploy/deploy.h"

class MotorControl {
public:
  MotorControl();

  bool stepper_line(int speed, int step_length, array_three current = array_three{100, 100, 100}); //这里的current的单位是实际长度单位
  bool stepper_circle(int r, int speed, int dir, int step_length);


// 一下的位置参数是步进电机移动步数
private:
  bool _writer(int16_t code, int speed);    //用于写入步进电机控制的I2C代码

  bool _stepper_X(int speed, int dir);    //步进电机单步控制
  bool _stepper_Y(int speed, int dir);
  bool _stepper_Z(int speed, int dir);

  bool _stepper_XY(int speed, int dir_x, int dir_y);
  bool _stepper_XZ(int speed, int dir_x, int dir_z);
  bool _stepper_YZ(int speed, int dir_y, int dir_z);

  bool _stepper_XYZ(int speed, int dir_x, int dir_y, int dir_z);


  bool _stepper_recursion(int speed);
  array_three _current={0, 0, 0};
};

#endif