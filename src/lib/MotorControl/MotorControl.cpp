#include "lib/MotorControl/MotorControl.h"


MotorControl::MotorControl(){
    //初始化I2C所需的引脚

    pinMode(I2S_OUT_BCK, OUTPUT);
    pinMode(I2S_OUT_WS, OUTPUT);
    pinMode(I2S_OUT_DATA, OUTPUT);

    Serial.print("步进电机 已启动");
}

bool MotorControl::stepper_circle(int r, int speed, int dir, int step_length){
    //TODO
}

bool MotorControl::stepper_goto(int speed, NumListThree position_puporse, NumListThree position_current){
    Serial.println("a1");
    Serial.print(position_puporse[0]);
    Serial.print(position_puporse[1]);
    Serial.println(position_puporse[2]);

    Serial.print(position_current[0]);
    Serial.print(position_current[1]);
    Serial.println(position_current[2]);

    NumList codes;
    while(position_current[0] != position_puporse[0] || position_current[1] != position_puporse[1] || position_current[2] != position_puporse[2]){
        Serial.println("a2");
        float datum = std::max({abs(position_puporse[0] - position_current[0]), 
                                abs(position_puporse[1] - position_current[1]), 
                                abs(position_puporse[2] - position_current[2])});

        datum = 1/datum;


        NumListThree move;

        float _x = (position_puporse[0] - position_current[0]) * datum;
        float _y = (position_puporse[1] - position_current[1]) * datum;
        float _z = (position_puporse[2] - position_current[2]) * datum;

        move[0] = (_x > 0) ? 1 : ((_x < 0) ? -1 : 0);
        move[1] = (_y > 0) ? 1 : ((_y < 0) ? -1 : 0);
        move[2] = (_z > 0) ? 1 : ((_z < 0) ? -1 : 0);


        int code = _code_writer(move);
        codes.push_back(code);

        position_current[0] += move[0];
        position_current[1] += move[1];
        position_current[2] += move[2];
    }
    
    for(int i = STEPLONGTH; i > 0; i--){
        for(int j = 0; j < codes.size(); j++){
            _writer(codes[j], speed);
        }
        
    }

    return true;
}

bool MotorControl::stepper_stop(){
    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, STEPER_NONE);
    digitalWrite(I2S_OUT_WS, HIGH);
    return true;
}

//------------------一下为psoitive部分-----------------

bool MotorControl::_writer(int16_t code, int step_time){
    //TODO
    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, code&0b00101010);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(SPEED-step_time);

    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, code);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(SPEED-step_time);

    return true;
}

int MotorControl::_code_writer(NumListThree move){
    int x = move[0];
    int y = move[1];
    int z = move[2];

    uint8_t code = 0b00000000;

    if(x==1) code |= PINS_X_forward;
    else if(x==-1) code |= PINS_X_backward;

    if(y==1) code |= PINS_Y_forward;
    else if(y==-1) code |= PINS_Y_backward;

    if(z==1) code |= PINS_Z_forward;
    else if(z==-1) code |= PINS_Z_backward;

    return code;
}

