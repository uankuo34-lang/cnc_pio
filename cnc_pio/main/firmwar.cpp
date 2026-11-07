// #include "MotorMotion.h"
// #include "SdControl.h"
// #include "WiFiCommunication.h"
// #include "lib.h"

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
//   Serial.println("系统初始化完成");

//   MotorMotion motorMotion{};
//   SdControl sdControl{};
//   WiFiCommunication wifiCommunication{};
//   GCodeParser gCodeParser{};

//   NumListThree position_puporse = NumListThree{0, 0, 0};
//   NumListThree position_current = NumListThree{0, 0, 0};
//   NumListThree origin = NumListThree{0, 0, 0};

//   sdControl.begin("test.nc", "r");

//   while (true) {
//     /* code */
//     String code = sdControl.read_line();

//     Serial.println(code);

//     char buffer[code.length() + 1]; // 将string格式转位char列表
//     code.toCharArray(buffer, sizeof(buffer));
//     gCodeParser.ParseLine(buffer);

//     if (gCodeParser.HasWord('G')) {
//       if ((int)gCodeParser.GetWordValue('G') == 1) {
//         if (gCodeParser.HasWord('X')) {
//           position_puporse[0] = gCodeParser.GetWordValue('X');
//         }
//         if (gCodeParser.HasWord('Y')) {
//           position_puporse[1] = gCodeParser.GetWordValue('Y');
//         }
//         if (gCodeParser.HasWord('Z')) {
//           position_puporse[2] = gCodeParser.GetWordValue('Z');
//         }

//         motorMotion.stepper_goto(position_puporse, position_current, 900);
//         position_current[0] = position_puporse[0];
//         position_current[1] = position_puporse[1];
//         position_current[2] = position_puporse[2];

//       }

//       else if ((int)gCodeParser.GetWordValue('G') == 2) {
//         if (gCodeParser.HasWord('X')) {
//           position_puporse[0] = gCodeParser.GetWordValue('X');
//         }
//         if (gCodeParser.HasWord('Y')) {
//           position_puporse[1] = gCodeParser.GetWordValue('Y');
//         }
//         if (gCodeParser.HasWord('Z')) {
//           position_puporse[2] = gCodeParser.GetWordValue('Z');
//         }
//         if (gCodeParser.HasWord('I')) {
//           origin[0] = position_current[0] + gCodeParser.GetWordValue('I');
//         }
//         if (gCodeParser.HasWord('J')) {
//           origin[1] = position_current[1] + gCodeParser.GetWordValue('J');
//         }

//         motorMotion.stepper_circle(origin, position_puporse,
//         position_current,
//                                    900, 1, 100);

//         position_current[0] = position_puporse[0];
//         position_current[1] = position_puporse[1];
//         position_current[2] = position_puporse[2];
//       }

//       else if ((int)gCodeParser.GetWordValue('G') == 3) {
//         if (gCodeParser.HasWord('X')) {
//           position_puporse[0] = gCodeParser.GetWordValue('X');
//         }
//         if (gCodeParser.HasWord('Y')) {
//           position_puporse[1] = gCodeParser.GetWordValue('Y');
//         }
//         if (gCodeParser.HasWord('Z')) {
//           position_puporse[2] = gCodeParser.GetWordValue('Z');
//         }
//         if (gCodeParser.HasWord('I')) {
//           origin[0] = position_current[0] + gCodeParser.GetWordValue('I');
//         }
//         if (gCodeParser.HasWord('J')) {
//           origin[1] = position_current[1] + gCodeParser.GetWordValue('J');
//         }

//         motorMotion.stepper_circle(origin, position_puporse,
//         position_current,
//                                    900, 0, 100);

//         position_current[0] = position_puporse[0];
//         position_current[1] = position_puporse[1];
//         position_current[2] = position_puporse[2];
//       }
//     }
//   }
// }
// void loop() {}

#include "MotorMotion.h"
#include "Probe.h"
#include "lib.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("hello world");

  MotorMotion motorMotion{};
  Probe probe{};

  motorMotion.begin();
  probe.begin();

  PosList probe_points = probe.probe(NumListThree{90, 90, 10}, NumListThree{0, 0, 10}, 500);

  for (int i = probe_points.size() - 1; i >= 0; i--) {
    Serial.print("X:");
    Serial.print(probe_points[i][0]);
    Serial.print(" Y:");
    Serial.print(probe_points[i][1]);
    Serial.print(" Z:");
    Serial.println(probe_points[i][2]);
  }

  Serial.println("完成");
}

void loop() {}