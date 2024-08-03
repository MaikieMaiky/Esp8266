#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>       // 用于多WiFi连接

// esp8266 Wireless station Study
// esp8266 无线终端学习



const char* ssid = "C++";       // the name of the Wi-Fi network -- 连接的WiFi名称
const char* password = "309309309"; // the password of the Wi-Fi network -- 连接的WiFi密码

ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'


void setup()
{
    // 单WiFi连接
    /* Serial.begin(9600);

    // connect to WiFi
    WiFi.begin(ssid, password);         // 启动WiFi连接
    Serial.print("Connecting to ");     // 打印连接信息
    Serial.println(ssid);Serial.println("...");               // 尝试连接交互文本

    uint16_t i = 0;
    while (WiFi.status() != WL_CONNECTED) { // 等待连接成功
        delay(1000);
        Serial.print(++i); Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("Connection established!"); // 连接成功
    Serial.print("IP address:    ");
    Serial.println(WiFi.localIP()); // 打印IP地址 */


    // 多WiFi连接
    Serial.begin(9600);

    // add WiFis -- 添加WiFi
    wifiMulti.addAP("C++", "309309309");   // 添加WiFi名称和密码
    wifiMulti.addAP("c++", "12345678");   // 添加WiFi名称和密码

    Serial.println("Connecting ...");     // 连接提示
    while (wifiMulti.run() != WL_CONNECTED) 
    { 
        // 等待连接成功 此处的wifiMulti.run()是重点。通过wifiMulti.run()，
        // NodeMCU将会在当前环境中搜索addAP函数所存储的WiFi。
        // 如果搜到多个存储的WiFi那么NodeMCU将会连接信号最强的那一个WiFi信号。
        // 一旦连接WiFI成功，wifiMuLti.run()将会返回"WL_CONNECTED”。
        // 这也是此处while循环判断是否跳出循环的条件。
        delay(1000);
        Serial.print('.');
    }

    Serial.println('\n');
    Serial.println("Connected to "); // 连接成功
    Serial.println(WiFi.SSID()); // 打印WiFi名称
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP()); // 打印IP地址
}

void loop()
{
    // put your main code here, to run repeatedly:
}
