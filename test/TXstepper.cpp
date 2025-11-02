#include <Arduino.h>

#define I2S_OUT_BCK             GPIO_NUM_22
#define I2S_OUT_WS              GPIO_NUM_17
#define I2S_OUT_DATA            GPIO_NUM_21
u_int8_t PINS_X = 10000010;
u_int8_t VOID = 0000000;

u_int8_t UNLOCK = 1000000;


void setup(){
    pinMode(I2S_OUT_BCK, OUTPUT);
    pinMode(I2S_OUT_WS, OUTPUT);
    pinMode(I2S_OUT_DATA, OUTPUT);

    digitalWrite(I2S_OUT_WS, LOW); 
    shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, UNLOCK);
    delayMicroseconds(100);
    digitalWrite(I2S_OUT_WS, HIGH);
}

void loop(){
        digitalWrite(I2S_OUT_WS, LOW); 
        shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, PINS_X);
        delayMicroseconds(100);
        digitalWrite(I2S_OUT_WS, HIGH);

        delayMicroseconds(100);
        digitalWrite(I2S_OUT_WS, LOW);
        shiftOut(I2S_OUT_DATA, I2S_OUT_BCK, MSBFIRST, VOID);
        delayMicroseconds(100);
        digitalWrite(I2S_OUT_WS, HIGH);
}