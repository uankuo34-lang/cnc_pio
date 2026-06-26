#include <Arduino.h>
#include "MotorMotion.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("系统初始化完成");

    MotorMotion MotorMotion;

    MotorMotion.begin();
    MotorMotion.stepper_circle();
}

void loop() {

}
