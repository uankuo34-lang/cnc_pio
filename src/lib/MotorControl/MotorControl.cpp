#include "lib/MotorControl/MotorControl.h"

MotorControl::MotorControl(){

    pinMode(I2S_OUT_BCK, OUTPUT);
    pinMode(I2S_OUT_WS, OUTPUT);
    pinMode(I2S_OUT_DATA, OUTPUT);

    Serial.print("步进电机 已启动");
}

bool MotorControl::stepper_line(int speed, int step_length, array_three current){
    _current[0] = current[0] * step_length;
    _current[1] = current[1] * step_length;
    _current[2] = current[2] * step_length;

    _stepper_recursion(speed);
    return true;
}


//---------------------------一下为私有部分---------------------------

bool MotorControl::_writer(int16_t code, int speed){        //用于将不进电机命令翻译成I2C数据
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

bool MotorControl::_stepper_X(int speed, int dir){      //x轴步进
    _writer(PINS_X+(dir*DIR_X), speed);
    return true;
}

bool MotorControl::_stepper_Z(int speed, int dir){      //y轴步进
    _writer(PINS_Z+(dir*DIR_Z), speed);
    return true;
}

bool MotorControl::_stepper_Y(int speed, int dir){      //z轴步进
    _writer(PINS_Y+(dir*DIR_Y), speed);
    return true;
}

bool MotorControl::_stepper_XY(int speed, int dir_x, int dir_y){        //xy轴步进
    _writer(PINS_X+(dir_x*DIR_X) + PINS_Y+(dir_y*DIR_Y), speed);
    return true;
}

bool MotorControl::_stepper_XZ(int speed, int dir_x, int dir_z){        //xz轴步进
    _writer(PINS_X+(dir_x*DIR_X) + PINS_Z+(dir_z*DIR_Z), speed);
    return true;
}

bool MotorControl::_stepper_YZ(int speed, int dir_y, int dir_z){        //yz轴步进
    _writer(PINS_Y+(dir_y*DIR_Y) + PINS_Z+(dir_z*DIR_Z), speed);
    return true;
}

bool MotorControl::_stepper_XYZ(int speed, int dir_x, int dir_y, int dir_z){        //xyz轴步进
    _writer(PINS_X+(dir_x*DIR_X) + PINS_Y+(dir_y*DIR_Y) + PINS_Z+(dir_z*DIR_Z), speed);
    return true;
}

bool MotorControl::_stepper_recursion(int speed){

    //步进电机单步移动距离（是否移动）
    int _x = 1;
    int _y = abs((_current[1] - _destination[1])/(_current[0] - _destination[0]));
    int _z = abs((_current[2] - _destination[2])/(_current[0] - _destination[0]));
    //计算旋转方向
    int _x_dir = (_current[0] - _destination[0])/(abs(_current[0] - _destination[0]));
    int _y_dir = (_current[1] - _destination[1])/(abs(_current[1] - _destination[1]));
    int _z_dir = (_current[2] - _destination[2])/(abs(_current[2] - _destination[2]));
    //步进电机单步移动代码
    if(_x != 0 and _y == 0 and _z == 0){
        _stepper_X(speed, _x_dir);
    }
    else if(_x == 0 and  _y != 0 and _z == 0){
        _stepper_Y(speed, _y_dir);
    }
    else if(_x == 0 and _y == 0 and _z != 0){
        _stepper_Z(speed, _z_dir);
    }
    else if(_x != 0 and _y != 0 and _z == 0){
        _stepper_XY(speed, _x_dir, _y_dir);
    }
    else if(_x != 0 and _y == 0 and _z != 0){
        _stepper_XZ(speed, _x_dir, _z_dir);
    }
    else if(_x == 0 and _y != 0 and _z != 0){
        _stepper_YZ(speed, _y_dir, _z_dir);
    }
    else if(_x != 0 and _y != 0 and _z != 0){
        _stepper_XYZ(speed, _x_dir, _y_dir, _z_dir);
    }

    //计算新的当前位置
    _destination[0] = _current[0] - _x;
    _destination[1] = _current[1] - _y;
    _destination[2] = _current[2] - _z;

    //执行递归部分

    if(_destination == _current){
        return true;
    }
    else{
        _stepper_recursion(speed);
    }
    return false;
}