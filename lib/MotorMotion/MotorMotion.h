#ifndef MOTORMOTION_H
#define MOTORMOTION_H

// 引入必要的库
#include "lib.h"
#include "deploy.h"

class MotorMotion
{
public:
  MotorMotion();

  bool begin();

  MotorMotion balance(NumListTwo position_puporse = NumListTwo{100, 100},
                       NumListTwo position_current = NumListTwo{0, 0});

  // bool stepper_line(int speed = 500, int step_length, NumListThree position_puporse = NumListThree{100, 100, 100}); //这里的current的单位是实际长度单位
  bool stepper_circle(NumListThree origin = NumListThree{0, 0, 0},
                      NumListThree position_puporse = NumListThree{100, 0, 0},
                      NumListThree position_current = NumListThree{0, 100, 0},
                      int r = 100, int speed = 500, int degree = 1); // 圆弧移动

  bool stepper_goto(NumListThree position_puporse = NumListThree{100, 100, 100},
                    NumListThree position_current = NumListThree{0, 0, 0}, int speed = 500); // 直线移动

  bool stepper_stop();

private:
    bool _writer(int16_t code, int speed = 500);    //用于写入步进电机控制的I2C代码
    int _code_writer(int x, int y, int z);    //步进电机单步控制
};

#endif