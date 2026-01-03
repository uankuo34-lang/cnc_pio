//步进电机所使用的引脚

#define I2S_OUT_BCK             16
#define I2S_OUT_WS              17
#define I2S_OUT_DATA            21

#define PINS_X 0b01000000
#define PINS_Y 0b00010000
#define PINS_Z 0b00000100
#define NONE   0b00000000
#define LOCK   0b10000000

#define DIR_X 0b00100000
#define DIR_Y 0b00001000
#define DIR_Z 0b00000010

#define SPEED 1000  //用于默认速度（最慢速度） 以及 步进电机转换为速度时的参数

int NEW_X = 0;
int NEW_Y = 0;
int NEW_Z = 0;

//SD卡所使用的常量
#define SDCARD_MISO_PIN 12  // MISO (数据输入)
#define SDCARD_MOSI_PIN 13  // MOSI (数据输出)
#define SDCARD_SCK_PIN 14   // SCK (时钟)
#define SDCARD_SS_PIN 15    // 片选引脚 (Chip Select)

#define SPI_CLOCK SD_SCK_MHZ(4) // SD卡通信速度 (4MHz)

using StringList = std::vector<String>;
using Dictionarystd = std::unordered_map<int, int>;
