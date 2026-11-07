#include "Probe.h"

Probe::Probe() { Serial.println("步进电机 引用"); }

bool Probe::begin() {
  motorMotion.begin();
  pinMode(PROBE, INPUT);
  Serial.println("调平模块初始化");
  return true;
}

PosList Probe::probe(NumListThree puporse, NumListThree current, int speed) {
  int move_x = (puporse[0] - current[0]) / PROBE_CLARITY;
  int move_y = (puporse[1] - current[0]) / PROBE_CLARITY;

  double drop_len = 1 / STEPLONGTH;

  PosList probe_points = {};

  for (int i = math_util::squ(PROBE_CLARITY); i >= 0; i--) {
    motorMotion.stepper_goto(
        NumListThree{current[0], current[1], current[2]}, // 移动到测量点
        NumListThree{current[0] + (probeing_way[i][0] * move_x),
                     current[1] + (probeing_way[i][1] * move_y), current[2]},
        speed);
    current[0] += (probeing_way[i][0] * move_x);
    current[1] += (probeing_way[i][1] * move_y);

    Serial.print(current[0]);
    Serial.print(" ");
    Serial.println(current[1]);

    // 下移探头进行celiang

    for (int j = PROBE_MAX_Z_MOVE; j >= 0; j--) {
      motorWrite.writer(motorWrite.code_writer(0, 0, -1), PROBE_SPEED);

      current[2] -= drop_len;

      if (digitalRead(PROBE) == 0) {
        Serial.print("测量点成功记录：");
        Serial.println(current[2]);

        probe_points.push_back(
            NumListThree{current[0], current[1], current[2]});
      }
      for (j; j < PROBE_MAX_Z_MOVE; j++) { // 回到原始位置
        motorWrite.writer(motorWrite.code_writer(0, 0, 1), PROBE_SPEED);
      }
    }
  }
  return probe_points;
}
