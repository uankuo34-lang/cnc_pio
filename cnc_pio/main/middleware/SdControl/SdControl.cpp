#include "SdControl.h"

SdControl::SdControl() : spiClass(HSPI){
  spiClass.begin(SDCARD_SCK_PIN, SDCARD_MISO_PIN, SDCARD_MOSI_PIN, -1);     //初始化主办SD卡所在管线的SPI
  SdSpiConfig SD_CONFIG = SdSpiConfig(SDCARD_SS_PIN, DEDICATED_SPI, SPI_CLOCK, &spiClass);      //设置SD卡的谅解

  if (!sdFs.begin(SD_CONFIG)) {         //启动SD卡
    Serial.println("SD卡启动失败");
    sdFs.initErrorHalt();
  }
  Serial.print("SD卡已启动");
}

bool SdControl::begin(String addess, String mode){
  if(mode == "w"){
    fsFile = sdFs.open(addess.c_str(), FILE_WRITE);
    return true;
  }
  else if(mode == "r"){
    fsFile = sdFs.open(addess.c_str(), FILE_READ);
    return true;
  }
  return false;
}

bool SdControl::write(StringList text){
  if(!fsFile){
    Serial.println("文件打开失败");
    return false;
  }

  for(int i = 0; i < text.size(); i++){
    fsFile.println(text[i]);
    Serial.println(text[i]);
  }

  Serial.println("写入成功");
  fsFile.close();
  return true;
}

bool SdControl::write_line(String text){
  if(!fsFile){
    Serial.println("文件打开失败");
    return false;
  }

    fsFile.println(text);
    Serial.println(text);

  Serial.println("写入成功");
  fsFile.close();
  return true;
}

StringList SdControl::read(){
  StringList data = {};

  while(fsFile.available()){
    String line = fsFile.readStringUntil('\n');

    Serial.println(line);
    data.push_back(line);
  }

  fsFile.close();
  return data;
}

String SdControl::read_line(){

  String data = fsFile.readStringUntil('\n');

  Serial.println(data);

  return data;
}


