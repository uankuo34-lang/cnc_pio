#include "WiFiCommunication.h"

WiFiCommunication::WiFiCommunication(String ssid, String password):server(8080){
    Serial.println("wifi 已启动");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);     //启动Wi-Fi模块

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
        return;
    }
    else{
        Serial.println("链接成功");
        Serial.print("设备Wi-Fi地址:");
        Serial.println(WiFi.localIP());
        Serial.println();

        server.begin();
        Serial.println("服务器已启动");
        Serial.print("服务器端口为:");
        Serial.println("8080");
    }
}
bool WiFiCommunication::write(String text){

    WiFiClient client = server.available();

    if(client){
        while (client.connected()){
            Serial.print("发送给客户端的指令为:");
            Serial.println(text);

            client.print(millis());
            client.println(text);
        }

        client.stop();
        Serial.println("客户端已断开链接");

        return true;
    }
    return false;
}