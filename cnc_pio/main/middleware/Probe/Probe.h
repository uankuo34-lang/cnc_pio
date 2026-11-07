#ifndef PROBE_H
#define PROBE_H

// 引入必要的库
#include "MotorMotion.h"
#include "MotorWrite.h"

#include "deploy.h"
#include "lib.h"

class Probe {
public:
  Probe();

  bool begin();

  PosList probe(NumListThree puporse = NumListThree{100, 0, 0},
                NumListThree current = NumListThree{0, 100, 0},
                int speed = 500);

private:
  MotorMotion motorMotion;
  MotorWrite motorWrite;

};

#endif