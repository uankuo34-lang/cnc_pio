#include "MotorMotion.h"

MotorMotion::MotorMotion()
{
    // 初始化I2C所需的引脚
    Serial.println("步进电机 引用");
}

bool MotorMotion::begin()
{
    pinMode(I2S_OUT_BCK, OUTPUT);
    pinMode(I2S_OUT_WS, OUTPUT);
    pinMode(I2S_OUT_DATA, OUTPUT);

    Serial.print("步进电机 已启动");
    return 0;
}

bool MotorMotion::stepper_circle(NumListThree origin,
                                  NumListThree position_puporse,
                                  NumListThree position_current,
                                  int r, int speed, int degree)
{

    int direction = ((position_current[0] * position_current[1] * degree < 0) ? -1 : 1); // 计算移动方向

    NumList codes0; // 用于存储每个八方之一圆
    NumList codes1;
    NumList codes2;
    NumList codes3;
    NumList codes4;
    NumList codes5;
    NumList codes6;
    NumList codes7;

    NumList codes; // 总体的指令

    while (abs(position_current[0]) != abs(position_current[1]))
    {

        position_current[0] += direction;

        // 建立新的坐标系将圆弧移动到原点
        int x = position_current[0] - origin[0];
        int y = position_current[1] - origin[1];
        int z = position_current[2] - origin[2];

        // 计算点到圆心的距离
        int distance = x ^ 2 + (y - direction) ^ 2 - r ^ 2;
        int move1 = (distance > 0) ? 1 : ((distance < 0) ? -1 : 0);

        //拼装所有八分之一圆
        int code = 0;  
        code = _code_writer(direction, distance, 0); // 保存数据0
        codes0.push_back(code);
        code = _code_writer(distance, direction, 0); // 保存数据1
        codes1.push_back(code);
        code = _code_writer(distance, -direction, 0); // 保存数据2
        codes2.push_back(code);
        code = _code_writer(direction, -distance, 0); // 保存数据3
        codes3.push_back(code);
        code = _code_writer(-direction, -distance, 0); // 保存数据4
        codes4.push_back(code);
        code = _code_writer(-distance, -direction, 0); // 保存数据5
        codes5.push_back(code);
        code = _code_writer(-distance, direction, 0); // 保存数据6
        codes6.push_back(code);
        code = _code_writer(-direction, distance, 0); // 保存数据7
        codes7.push_back(code);
    }

    for (int i = STEPLONGTH; i > 0; i--) // 执行运动指令
    {
        for (int j = 0; j < codes.size(); j++)
        {
            if (position_current[0] != position_puporse[0] ||
                position_current[1] != position_puporse[1] ||
                position_current[2] != position_puporse[2])
            {
                return true;
            }
            else
            {
                Serial.println(codes[j]);
                _writer(codes[j], speed);
            }
        }
    }

    return false;   //应该永远不会返回false
}

bool MotorMotion::stepper_goto(NumListThree position_puporse, NumListThree position_current, int speed)
{
    Serial.println("a1");
    Serial.print(position_puporse[0]);
    Serial.print(position_puporse[1]);
    Serial.println(position_puporse[2]);

    Serial.print(position_current[0]);
    Serial.print(position_current[1]);
    Serial.println(position_current[2]);

    NumList codes;
    while (position_current[0] != position_puporse[0] ||
           position_current[1] != position_puporse[1] ||
           position_current[2] != position_puporse[2])
    {
        Serial.println("a2");
        float datum = std::max({abs(position_puporse[0] - position_current[0]), // 用于平移点击移动时所需的三角形到原点
                                abs(position_puporse[1] - position_current[1]),
                                abs(position_puporse[2] - position_current[2])});

        datum = 1 / datum;

        float _x = (position_puporse[0] - position_current[0]) * datum; // 计算每一步的移动距离
        float _y = (position_puporse[1] - position_current[1]) * datum;
        float _z = (position_puporse[2] - position_current[2]) * datum;

        int move0 = (_x > 0) ? 1 : ((_x < 0) ? -1 : 0); // 将移动方向的符号提取出
        int move1 = (_y > 0) ? 1 : ((_y < 0) ? -1 : 0);
        int move2 = (_z > 0) ? 1 : ((_z < 0) ? -1 : 0);

        int code = _code_writer(move0, move1, move2);
        codes.push_back(code);

        position_current[0] += move0;
        position_current[1] += move1;
        position_current[2] += move2;
    }
    

    for (int i = STEPLONGTH; i > 0; i--)
    {
        for (int j = 0; j < codes.size(); j++)
        {
            _writer(codes[j], speed);
        }
    }

    return true;
}

bool MotorMotion::stepper_stop()
{
    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, STEPER_NONE);
    digitalWrite(I2S_OUT_WS, HIGH);
    return true;
}

//------------------一下为psoitive部分-----------------

bool MotorMotion::_writer(int16_t code, int step_time)
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

int MotorMotion::_code_writer(int x, int y, int z)
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
