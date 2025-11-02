#include "WiFiCommunication.h"

WiFiCommunication::WiFiCommunication(String ssid, String password){
    Serial.println("wifi 已启动");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    short time = 30;
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
        time--;
        if(time == 0){
            break;
        }
    }
    if(time == 0){
        Serial.println("wifi 连接超时");
    }
    else{
        Serial.println("链接成功");
        Serial.print("设备Wi-Fi地址:");
        Serial.println(WiFi.localIP());
    }
}
WiFiCommunication::write(){
    
}