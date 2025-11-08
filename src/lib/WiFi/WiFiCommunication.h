#ifndef WIFICOMMUNICATION_H
#define WIFICOMMUNICATION_H

// 引入必要的库
#include "lib/lib/lib.h"
#include "lib/deploy/deploy.h"

class WiFiCommunication {
public:
  WiFiCommunication(String ssid, String password);

  bool write(String text);
  StringList read();

  bool exit();

private:
  WiFiServer _server;
  WiFiClient _client;
};
#endif