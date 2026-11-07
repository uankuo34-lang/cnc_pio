#ifndef MOTORWRITE_H
#define MOTORWRITE_H

// 引入必要的库
#include "lib.h"
#include "deploy.h"

class MotorWrite
{
public:
    MotorWrite();

    bool writer(int16_t code, int speed = 500); // 用于写入步进电机控制的I2C代码
    int code_writer(int x, int y, int z);       // 步进电机单步控制
};

#endif