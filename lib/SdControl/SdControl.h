#ifndef SDCONTROL_H
#define SDCONTROL_H

// 引入必要的库
#include "lib.h"
#include "deploy.h"

class SdControl {
public:
  SdControl();

  bool begin(String addess, String mode);
  bool write(StringList text);
  StringList read();
  String read_line();

private:
  SdFs _sd;
  FsFile _file;
  SPIClass _sd_spi;
};

#endif