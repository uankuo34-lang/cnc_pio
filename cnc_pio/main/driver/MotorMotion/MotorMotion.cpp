#include "MotorMotion.h"

MotorMotion::MotorMotion() { Serial.println("步进电机 引用"); }

bool MotorMotion::begin() {

  // 初始化I2C所需的引脚
  pinMode(I2S_OUT_BCK, OUTPUT);
  pinMode(I2S_OUT_WS, OUTPUT);
  pinMode(I2S_OUT_DATA, OUTPUT);

  Serial.println("步进电机运动逻辑 已启动");
  return true;
}

bool MotorMotion::stepper_circle(NumListThree origin, NumListThree puporse,
                                 NumListThree current, int speed, short degree,
                                 int clarity) {

  int ratio = STEPLONGTH / clarity; // 清晰度和实际步长的比例

  current[0] = (current[0] - origin[0]) *
               clarity; // 将实际距离转化为电机步数 并 移动到原点
  current[1] = (current[1] - origin[1]) * clarity;
  current[2] = (current[2] - origin[2]) * clarity;

  puporse[0] = (puporse[0] - origin[0]) * clarity; // 移动到原点
  puporse[1] = (puporse[1] - origin[1]) * clarity;
  puporse[2] = (puporse[2] - origin[2]) * clarity;

  int r = (math_util::squ(current[0]) + math_util::squ(current[1])) *
          math_util::squ(clarity);
  do {

    long long in_out = math_util::squ(current[0]) + math_util::squ(current[1]) -
                       r; // 计算在圆内还是在圆外

    bool move1 = abs(current[0]) > abs(current[1]);
    bool move2 = current[0] >= 0;
    bool move3 = current[1] > 0;
    bool move4 = (in_out > 0) == (degree > 0);

    short move =
        (move1 << 3) | (move2 << 2) | (move3 << 1) | (move4 << 0); // 计算移动码

    short x = motor_map[move][0] * degree;
    short y = motor_map[move][1] * degree;
    Serial.print(x);
    Serial.print(y);

    for (int i = ratio; i > 0; i--) {
      motorWrite.writer(motorWrite.code_writer(x, y, 0), speed);
    }
    current[0] += x;
    current[1] += y;

    Serial.print(current[0]);
    Serial.println(current[1]);

  } while (current[0] != puporse[0] || current[1] != puporse[1] ||
           current[2] != puporse[2]);
  return true;
}

bool MotorMotion::stepper_goto(NumListThree puporse, NumListThree current,
                               int speed) {
  Serial.println("a1");
  Serial.print(puporse[0]);
  Serial.print(puporse[1]);
  Serial.println(puporse[2]);

  Serial.print(current[0]);
  Serial.print(current[1]);
  Serial.println(current[2]);

  NumList codes;
  while (current[0] != puporse[0] || current[1] != puporse[1] ||
         current[2] != puporse[2]) {
    Serial.println("a2");
    float datum = std::max(
        {abs(puporse[0] - current[0]), // 用于平移点击移动时所需的三角形到原点
         abs(puporse[1] - current[1]), abs(puporse[2] - current[2])});

    datum = 1 / datum;

    float _x = (puporse[0] - current[0]) * datum; // 计算每一步的移动距离
    float _y = (puporse[1] - current[1]) * datum;
    float _z = (puporse[2] - current[2]) * datum;

    int move0 = (_x > 0) ? 1 : ((_x < 0) ? -1 : 0); // 将移动方向的符号提取出
    int move1 = (_y > 0) ? 1 : ((_y < 0) ? -1 : 0);
    int move2 = (_z > 0) ? 1 : ((_z < 0) ? -1 : 0);

    int code = motorWrite.code_writer(move0, move1, move2);
    codes.push_back(code);

    current[0] += move0;
    current[1] += move1;
    current[2] += move2;
  }

  for (int i = STEPLONGTH; i > 0; i--) {
    for (int j = 0; j < codes.size(); j++) {
      motorWrite.writer(codes[j], speed);
    }
  }

  return true;
}

bool MotorMotion::stepper_stop() {
  digitalWrite(I2S_OUT_WS, LOW);
  shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, STEPER_NONE);
  digitalWrite(I2S_OUT_WS, HIGH);
  return true;
}
