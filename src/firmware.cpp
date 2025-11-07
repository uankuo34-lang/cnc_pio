#include <lib/lib/lib.h>
#include <lib/WiFi/WiFiCommunication.h>

void setup(){
    Serial.begin(115200);
    Serial.println("程序已起动");
    WiFiCommunication WiFiCommunication("CMCC-Wm2n", "ghzbv5g8");

    for(int i=200; i >= 0; i--){
      String text = WiFiCommunication.read();
      Serial.println(text);
      vTaskDelay(500);
    }

    WiFiCommunication.exit();
    Serial.println("客户端已断开链接");
}
void loop(){
  //TODO
}