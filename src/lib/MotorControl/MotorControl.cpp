#include "lib/MotorControl/MotorControl.h"

MotorControl::MotorControl(){

    pinMode(I2S_OUT_BCK, OUTPUT);
    pinMode(I2S_OUT_WS, OUTPUT);
    pinMode(I2S_OUT_DATA, OUTPUT);

    Serial.print("步进电机 已启动");
}


bool MotorControl::_writer(int16_t code, int speed){
    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, code);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(SPEED-speed);

    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, NONE);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(SPEED-speed);

    return true;
}

//步进电机单步控制函数

bool MotorControl::_stepper_X(int speed, int dir){
    _writer(PINS_X+(dir*DIR_X), speed);
    return true;
}

bool MotorControl::_stepper_Z(int speed, int dir){
    _writer(PINS_Z+(dir*DIR_Z), speed);
    return true;
}

bool MotorControl::_stepper_Y(int speed, int dir){
    _writer(PINS_Y+(dir*DIR_Y), speed);
    return true;
}

bool MotorControl::_stepper_XY(int speed, int dir_x, int dir_y){
    _writer(PINS_X+(dir_x*DIR_X) + PINS_Y+(dir_y*DIR_Y), speed);
    return true;
}

bool MotorControl::_stepper_XZ(int speed, int dir_x, int dir_z){
    _writer(PINS_X+(dir_x*DIR_X) + PINS_Z+(dir_z*DIR_Z), speed);
    return true;
}

bool MotorControl::_stepper_YZ(int speed, int dir_y, int dir_z){
    _writer(PINS_Y+(dir_y*DIR_Y) + PINS_Z+(dir_z*DIR_Z), speed);
    return true;
}

bool MotorControl::_stepper_XYZ(int speed, int dir_x, int dir_y, int dir_z){
    _writer(PINS_X+(dir_x*DIR_X) + PINS_Y+(dir_y*DIR_Y) + PINS_Z+(dir_z*DIR_Z), speed);
    return true;
}