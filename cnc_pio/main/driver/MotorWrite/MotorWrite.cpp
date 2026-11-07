#include "MotorWrite.h"

MotorWrite::MotorWrite()
{
    // 初始化I2C所需的引脚
    Serial.println("步进电机驱动 引用");
}

bool MotorWrite::writer(int16_t code, int step_time)
{ // 用于电机的每一步的移动

    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, code & 0b00101010);
    digitalWrite(I2S_OUT_WS, HIGH);

    delayMicroseconds(SPEED - step_time);

    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, code);
    digitalWrite(I2S_OUT_WS, HIGH);

    delayMicroseconds(SPEED - step_time);

    return true;
}

int MotorWrite::code_writer(int x, int y, int z)
{ // 用于将不同方向的电机移动方向合并为一条指令

    uint8_t code = 0b00000000;

    if (x == 1)
        code |= PINS_X_forward;
    else if (x == -1)
        code |= PINS_X_backward;

    if (y == 1)
        code |= PINS_Y_forward;
    else if (y == -1)
        code |= PINS_Y_backward;

    if (z == 1)
        code |= PINS_Z_forward;
    else if (z == -1)
        code |= PINS_Z_backward;

    return code;
}

