#include "lib/MotorControl/MotorControl.h"
#include "lib/SdControl/SdControl.h"
#include "lib/lib/lib.h"



void setup(){
    Serial.begin(115200);
    Serial.println("hello world 111");

    MotorControl MotorControl;
    GCodeParser GCodeParser;
    SdControl SdControl;

    NumListThree position_puporse = NumListThree{0, 0, 0};
    NumListThree position_current = NumListThree{0, 0, 0};

    SdControl.begin("aaa.txt", "r");

    while (true){
        String code = SdControl.read_line();

        Serial.println(code);

        char buffer[code.length() + 1]; 
        code.toCharArray(buffer, sizeof(buffer)); 
        GCodeParser.ParseLine(buffer);

        if(GCodeParser.HasWord('G')){
            if((int)GCodeParser.GetWordValue('G') == 1){
                Serial.println("b1");
                if(GCodeParser.HasWord('X')){
                    position_puporse[0] = GCodeParser.GetWordValue('X');
                }
                if(GCodeParser.HasWord('Y')){
                    position_puporse[1] = GCodeParser.GetWordValue('Y');
                }
                if(GCodeParser.HasWord('Z')){
                    position_puporse[2] = GCodeParser.GetWordValue('Z');
                }
                Serial.println("b2");

                Serial.println(position_puporse[0]);
                Serial.println(position_puporse[1]);
                Serial.println(position_puporse[2]);

                MotorControl.stepper_goto(900, position_puporse, position_current);
                for (int i = 0; i < 3; i++) {
                    position_current[i] = position_puporse[i];
                }
            }
        }
        Serial.println("_______________aaa_______________");
    }
    MotorControl.stepper_stop();
}
void loop(){
    
}
