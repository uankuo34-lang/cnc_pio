#include "lib/MotorControl/MotorControl.h"


MotorControl::MotorControl(){

}

bool MotorControl::stepper_x(double distance, int speed, int step_length){
  Serial.println("stepper_x");
  for(int i=0; i < (int)(distance/step_length); i++){       //横坐标移动距离 Step = L/l

    digitalWrite(I2S_OUT_WS, LOW); 
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, PINS_X);
    delay(SPEED-speed);
    digitalWrite(I2S_OUT_WS, HIGH);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, VOID);
    delay(SPEED-speed);
    digitalWrite(I2S_OUT_WS, HIGH);
  }
  return true;
}

bool MotorControl::stepper_y(double distance, int speed, int step_length){
  Serial.println("stepper_y");
  for(int i=0; i < (int)(distance/step_length); i++){       //纵坐标移动距离 Step = L/l

    digitalWrite(I2S_OUT_WS, LOW); 
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, PINS_Y);
    delay(SPEED-speed);
    digitalWrite(I2S_OUT_WS, HIGH);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, VOID);
    delay(SPEED-speed);
    digitalWrite(I2S_OUT_WS, HIGH);
  }
  return true;
}

bool MotorControl::stepper_z(double distance, int speed, int step_length){
  Serial.println("stepper_z");
  for(int i=0; i < (int)(distance/step_length); i++){       //高坐标移动距离 Step = L/l

    digitalWrite(I2S_OUT_WS, LOW); 
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, PINS_Z);
    delay(SPEED-speed);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, VOID);
    digitalWrite(I2S_OUT_WS, HIGH);
    delay(SPEED-speed);
  }
  return true;
}