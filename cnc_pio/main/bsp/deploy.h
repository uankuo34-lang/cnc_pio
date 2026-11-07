#ifndef DEPLOY_H_ // 安全头卫视
#define DEPLOY_H_

using StringList = std::vector<String>;

using NumListTwo = std::array<double, 2>;
using NumListThree = std::array<double, 3>;

using NumList = std::vector<double>;
using PosList = std::vector<NumListThree>;

// 步进电机所使用的引脚
#define I2S_OUT_BCK 16
#define I2S_OUT_WS 17
#define I2S_OUT_DATA 21
#define PROBE 22

// 向控制器传入一下代码后就会移动一下
#define PINS_X_forward 0b01000000  // 正向X轴
#define PINS_X_backward 0b01100000 // 反向X轴
#define PINS_Y_forward 0b00000100
#define PINS_Y_backward 0b00000110
#define PINS_Z_forward 0b00010000
#define PINS_Z_backward 0b00011000

#define STEPER_NONE 0b10000000
#define STEPER_LOCK 0b00000000 // 最好不要用 会让电机发热并毁掉启动器

#define PROBE_CLARITY 9
#define PROBE_MAX_Z_MOVE 400000

inline std::unordered_map<int, NumListTwo> motor_map = {
    {0b0111, NumListTwo{1, -1}},  {0b0110, NumListTwo{1, 0}},
    {0b1111, NumListTwo{0, -1}},  {0b1110, NumListTwo{1, -1}},
    {0b1101, NumListTwo{-1, -1}}, {0b1100, NumListTwo{0, -1}},
    {0b0101, NumListTwo{-1, 0}},  {0b0100, NumListTwo{-1, -1}},
    {0b0001, NumListTwo{-1, 1}},  {0b0000, NumListTwo{-1, 0}},
    {0b1001, NumListTwo{0, 1}},   {0b1000, NumListTwo{-1, 1}},
    {0b1011, NumListTwo{1, 1}},   {0b1010, NumListTwo{0, 1}},
    {0b0011, NumListTwo{1, 0}},   {0b0010, NumListTwo{1, 1}}};

inline std::vector<NumListTwo> probeing_way = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0},
    {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1},
    {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2},
    {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3},
    {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4},
    {8, 5}, {7, 5}, {6, 5}, {5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5},
    {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6}, {8, 6},
    {8, 7}, {7, 7}, {6, 7}, {5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7},
    {0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}
};

#define SPEED 1000     // 步进电机转换为速度时的参数
#define STEPLONGTH 800 // 步进电机转换为步长时的参数
#define PROBE_SPEED 100 // 探针移动速度

// SD卡所使用的常量
#define SDCARD_MISO_PIN 12 // MISO (数据输入)
#define SDCARD_MOSI_PIN 13 // MOSI (数据输出)
#define SDCARD_SCK_PIN 14  // SCK (时钟)
#define SDCARD_SS_PIN 15   // 片选引脚 (Chip Select)

#define SPI_CLOCK SD_SCK_MHZ(4) // SD卡通信速度 (4MHz)

namespace math_util {
template <typename T> inline int sgn(T val) { return (val > 0) - (val < 0); }
template <typename T> inline int sgn_ceiling(T val) {
  return (val > 0) ? 1 : -1;
}
template <typename T> inline int sgn_floor(T val) {
  return (val >= 0) ? 1 : -1;
}

template <typename T> inline int squ(T val) { return val * val; }
} // namespace math_util

#endif