#include "lib/lib/lib.h"
#include "lib/MotorControl/MotorControl.h"
// #include "lib/MotorControl/MotorControl.h"


void setup(){
  MotorControl MotorControl;
  Serial.begin(115200);
  Serial.println("setup");

  for(int i=0; i < 10; i++){
    Serial.print("working");
    Serial.println(i);
    MotorControl.stepper_x(10, 10, 800);
    MotorControl.stepper_y(10, 10, 800);
  }
}

void loop(){

}