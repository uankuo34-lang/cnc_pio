using StringList = std::vector<String>;
using NumList = std::vector<int>;
using NumListThree = std::array<int, 3>;

//步进电机所使用的引脚
#define I2S_OUT_BCK             16
#define I2S_OUT_WS              17
#define I2S_OUT_DATA            21

//向控制器传入一下代码后就会移动一下
#define PINS_X_forward  0b01000000       //正向X轴
#define PINS_X_backward 0b01100000       //反向X轴
#define PINS_Y_forward  0b00000100
#define PINS_Y_backward 0b00000110
#define PINS_Z_forward  0b00010000 
#define PINS_Z_backward 0b00011000

#define STEPER_NONE   0b10000000
#define STEPER_LOCK   0b00000000       //最好不要用 会让电机发热并毁掉启动器

#define SPEED 1000  //步进电机转换为速度时的参数
#define STEPLONGTH 800  //步进电机转换为步长时的参数

//SD卡所使用的常量
#define SDCARD_MISO_PIN 12  // MISO (数据输入)
#define SDCARD_MOSI_PIN 13  // MOSI (数据输出)
#define SDCARD_SCK_PIN 14   // SCK (时钟)
#define SDCARD_SS_PIN 15    // 片选引脚 (Chip Select)

#define SPI_CLOCK SD_SCK_MHZ(4) // SD卡通信速度 (4MHz)
