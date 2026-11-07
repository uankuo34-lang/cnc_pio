#ifndef MOTORMOTION_H
#define MOTORMOTION_H

// 引入必要的库
#include "MotorWrite.h"
#include "deploy.h"
#include "lib.h"

class MotorMotion {
public:
  MotorMotion();

  bool begin();

  // MotorMotion balance(NumListTwo puporse = NumListTwo{100, 100},
  //                      NumListTwo current = NumListTwo{0, 0});

  // bool stepper_line(int speed = 500, int step_length, NumListThree puporse =
  // NumListThree{100, 100, 100}); //这里的current的单位是实际长度单位
  bool stepper_circle(NumListThree origin = NumListThree{0, 0, 0},
                      NumListThree puporse = NumListThree{100, 0, 0},
                      NumListThree current = NumListThree{0, 100, 0},
                      int speed = 500, short degree = 1,
                      int clarity = 100); // 圆弧移动

  bool stepper_goto(NumListThree puporse = NumListThree{100, 100, 100},
                    NumListThree current = NumListThree{0, 0, 0},
                    int speed = 500); // 直线移动

  bool stepper_stop();

private:
  MotorWrite motorWrite;
};

#endif