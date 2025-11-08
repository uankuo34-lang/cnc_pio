#include "WiFiCommunication.h"

WiFiCommunication::WiFiCommunication(String ssid, String password):_server(8080){
    Serial.println("wifi 已启动");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);     //启动Wi-Fi模块

    short time = 30;
    while (WiFi.status() != WL_CONNECTED){
        vTaskDelay(500);
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
        Serial.println("连接成功");
        Serial.print("设备Wi-Fi地址:");
        Serial.println(WiFi.localIP());
        Serial.println();

        _server.begin();
        Serial.println("服务器已启动");
        Serial.print("服务器端口为:");
        Serial.println("8080");
        
        while (!_client){

            WiFiClient client = _server.available();
            if(client){
                _client = client;
                Serial.println("\n客户端已连接");
                break;
            }
            vTaskDelay(500);
            Serial.print(".");
        }
    }
}
bool WiFiCommunication::write(String text){
    
    if (_client.connected()){
        Serial.print("发送给客户端的指令为:");
        Serial.println(text);

        _client.print(millis());
        _client.print(" >>> ");
        _client.println(text);

        return true;
    }
    return false;
}

StringList WiFiCommunication::read(){

    if (_client.connected()){

        StringList data = {};
        while(true){
            String text = _client.readStringUntil(' ');
            if (text.length() > 1){
                if(text[text.length()-1] == '\n'){
                    text = text.substring(0, text.length()-2);
                }
                else{
                    text=text.substring(0, text.length()-1);
                }
                data.push_back(text);
            }
            else{
                break;
            }
        }
        return data;
    }
    return {"0"};
}

bool WiFiCommunication::exit(){
    _client.stop();
    Serial.println("客户端已断开链接");

    return true;
}