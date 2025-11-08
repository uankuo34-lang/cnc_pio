//步进电机所使用的引脚

#define I2S_OUT_BCK             22
#define I2S_OUT_WS              17
#define I2S_OUT_DATA            21

#define PINS_X 0b1000001
#define PINS_Y 0b1000010
#define PINS_Z 0b1000011
#define VOID   0b1000000

#define SPEED 1000

//SD卡所使用的常量
#define SDCARD_MISO_PIN 12  // MISO (数据输入)
#define SDCARD_MOSI_PIN 13  // MOSI (数据输出)
#define SDCARD_SCK_PIN 14   // SCK (时钟)
#define SDCARD_SS_PIN 15    // 片选引脚 (Chip Select)

#define SPI_CLOCK SD_SCK_MHZ(4) // SD卡通信速度 (4MHz)

using StringList = std::vector<String>;
