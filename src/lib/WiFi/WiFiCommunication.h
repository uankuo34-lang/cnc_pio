#ifndef WIFICOMMUNICATION_H
#define WIFICOMMUNICATION_H

// 引入必要的库
#include "lib/lib/lib.h"
#include "lib/pins/pins.h"

class WiFiCommunication {
public:
  WiFiCommunication(String ssid, String password);

  bool write(String text);
  String read();
};

#endif