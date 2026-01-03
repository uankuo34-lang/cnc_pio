#include "lib/SdControl/SdControl.h"

SdControl::SdControl() : _sd_spi(HSPI){
  _sd_spi.begin(SDCARD_SCK_PIN, SDCARD_MISO_PIN, SDCARD_MOSI_PIN, -1);     //初始化主办SD卡所在管线的SPI
  SdSpiConfig SD_CONFIG = SdSpiConfig(SDCARD_SS_PIN, DEDICATED_SPI, SPI_CLOCK, &_sd_spi);      //设置SD卡的谅解

  if (!_sd.begin(SD_CONFIG)) {         //启动SD卡
    Serial.println("SD卡启动失败");
    _sd.initErrorHalt();
  }
  Serial.print("SD卡已启动");
}

bool SdControl::write(String addess, StringList text){

  _file = _sd.open(addess.c_str(), FILE_WRITE);     //打开文件 如果没有就创建

  if(!_file){
    Serial.println("文件打开失败");
    return false;
  }

  for(int i = 0; i < text.size(); i++){
    _file.println(text[i]);
    Serial.println(text[i]);
  }

  Serial.println("写入成功");
  _file.close();
  return true;
}

StringList SdControl::read(String addess){
  _file = _sd.open(addess.c_str(), FILE_READ);
  StringList data = {};

  while(_file.available()){
    String line = _file.readStringUntil('\n');

    Serial.println(line);
    data.push_back(line);
  }

  _file.close();
  return data;
}

