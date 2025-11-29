#include <Arduino.h>

#define I2S_OUT_BCK             16      //正确的引脚
#define I2S_OUT_WS              17
#define I2S_OUT_DATA            21
u_int8_t LOCK = 0b10000000;
u_int8_t direction = 0b10000010;
u_int8_t PINS_X = 0b10000001;

u_int8_t VOID = 0b00000000;




void setup(){
    pinMode(I2S_OUT_BCK, OUTPUT);
    pinMode(I2S_OUT_WS, OUTPUT);
    pinMode(I2S_OUT_DATA, OUTPUT);

    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, LOCK);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(100);

    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, direction);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(100);


}

void loop(){
        digitalWrite(I2S_OUT_WS, LOW);
        shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, PINS_X);
        digitalWrite(I2S_OUT_WS, HIGH);
        delayMicroseconds(100);

        digitalWrite(I2S_OUT_WS, LOW);
        shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, VOID);
        digitalWrite(I2S_OUT_WS, HIGH);
        delayMicroseconds(100);
}