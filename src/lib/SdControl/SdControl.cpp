#include "lib/SdControl/SdControl.h"

SdControl::SdControl() : sd_spi(HSPI){
  sd_spi.begin(SDCARD_SCK_PIN, SDCARD_MISO_PIN, SDCARD_MOSI_PIN, -1);     //初始化主办SD卡所在管线的SPI
  SdSpiConfig SD_CONFIG = SdSpiConfig(SDCARD_SS_PIN, DEDICATED_SPI, SPI_CLOCK, &sd_spi);      //设置SD卡的谅解

  if (!sd.begin(SD_CONFIG)) {         //启动SD卡
    Serial.println("SD卡启动失败");
    sd.initErrorHalt();
  }
}

bool SdControl::write(String addess, StringList text){

  file = sd.open(addess.c_str(), FILE_WRITE);     //打开文件 如果没有就创建

  if(!file){
    Serial.println("文件打开失败");
    return false;
  }

  for(int i = 0; i < text.size(); i++){
    file.println(text[i]);
    Serial.println(text[i]);
  }

  Serial.println("写入成功");
  file.close();
  return true; 
}

StringList SdControl::read(String addess){
  file = sd.open(addess.c_str(), FILE_READ);
  std::vector<String> data = {};

  while(file.available()){
    String line = file.readStringUntil('\n');

    Serial.println(line);   
    data.push_back(line);
  }
  
  file.close();
  return data;
}

