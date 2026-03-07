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

bool SdControl::begin(String addess, String mode){
  if(mode == "w"){
    _file = _sd.open(addess.c_str(), FILE_WRITE);
    return true;
  }
  else if(mode == "r"){
    _file = _sd.open(addess.c_str(), FILE_READ);
    return true;
  }
  return false;
}

bool SdControl::write(StringList text){
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

StringList SdControl::read(){
  StringList data = {};

  while(_file.available()){
    String line = _file.readStringUntil('\n');

    Serial.println(line);
    data.push_back(line);
  }

  _file.close();
  return data;
}

String SdControl::read_line(){

  String data = _file.readStringUntil('\n');

  Serial.println(data);

  return data;
}


