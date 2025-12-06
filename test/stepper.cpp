#include <Arduino.h>

#define I2S_OUT_BCK             16      //正确的引脚
#define I2S_OUT_WS              17
#define I2S_OUT_DATA            21

u_int8_t PINS_X_A = 0b00000000;
u_int8_t PINS_X_B = 0b01000000;


void setup(){
    pinMode(I2S_OUT_BCK, OUTPUT);
    pinMode(I2S_OUT_WS, OUTPUT);
    pinMode(I2S_OUT_DATA, OUTPUT);

}

void loop(){
    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, PINS_X_A);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(100);

    digitalWrite(I2S_OUT_WS, LOW);
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, LSBFIRST, PINS_X_B);
    digitalWrite(I2S_OUT_WS, HIGH);
    delayMicroseconds(100);
}