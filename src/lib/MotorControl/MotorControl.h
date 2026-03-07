#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// 引入必要的库
#include "lib/lib/lib.h"
#include "lib/deploy/deploy.h"

class MotorControl {
public:
  MotorControl();

  // bool stepper_line(int speed = 500, int step_length, NumListThree position_puporse = NumListThree{100, 100, 100}); //这里的current的单位是实际长度单位
  bool stepper_circle(int r, int speed, int dir, int step_length);
  bool stepper_goto(int speed = 500, NumListThree position_puporse = NumListThree{100, 100, 100}, NumListThree position_current = NumListThree{0, 0, 0});    //步进电机移动到指定位置 这是一个递归函数 请注意内存释放
  bool stepper_stop();

// 一下的位置参数是步进电机移动步数
private:
  bool _writer(int16_t code, int speed = 500);    //用于写入步进电机控制的I2C代码

  int _code_writer(NumListThree move = NumListThree{0, 0, 0});    //步进电机单步控制
};

#endif