#ifndef SDCONTROL_H
#define SDCONTROL_H

// 引入必要的库
#include "lib/lib/lib.h"
#include "lib/pins/pins.h"

using StringList = std::vector<String>;

class SdControl {
public:
  SdControl();

  bool write(String addess, StringList text);
  StringList read(String addess);

private:
  SdFs _sd;
  FsFile _file;
  SPIClass _sd_spi;
};

#endif