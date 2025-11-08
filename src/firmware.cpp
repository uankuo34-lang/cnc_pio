#include <lib/lib/lib.h>
#include <lib/WiFi/WiFiCommunication.h>

void setup(){
    Serial.begin(115200);
    Serial.println("程序已起动");
    WiFiCommunication WiFiCommunication("CMCC-Wm2n", "ghzbv5g8");

    while(true){
      StringList text = WiFiCommunication.read();

      if(text.size() > 0){
        for(int i=text.size()-1; i >= 0; i--){

        Serial.println(text[i]);
        Serial.print("  ");

        if(text[i] == "exit()"){
          WiFiCommunication.exit();
          return;
        }
      }
      Serial.println("");
      vTaskDelay(250);
      }
    }
}
void loop(){
  //TODO
}

