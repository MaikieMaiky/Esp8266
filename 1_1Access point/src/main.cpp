#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

// esp8266 nodeMCU Access Point Study
// 接入点模式类似于路由器，可以连接多个设备
// 可以打开串口看看实验现象啦 应该会看到一串乱码之后就是正常的内容啦


const char *ssid     = "bige-maker";      // SSID (Service Set Identifier) of the Access Point --  WIFI名称
const char *password = "12345678"; // Password of the Access Point -- WIFI密码

ESP8266WiFiMulti wifiMulti; // Create an instance of the ESP8266WiFiMulti class -- 创建一个ESP8266WiFiMulti类的实例

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600); // Initialize the Serial interface with a baud rate of 9600 -- 初始化串口，波特率为9600

    WiFi.softAP(ssid, password); // Start the Access Point -- 启动接入点

    Serial.print("\nAccess Point: ");  // Print the Access Point SSID -- 打印接入点SSID
    Serial.println(ssid);            // Print the Access Point password -- 打印接入点密码
    Serial.print("IP Address: ");    // Print the IP address of the Access Point -- 打印接入点的IP地址
    Serial.println(WiFi.softAPIP()); // Print the IP address of the Access Point -- 打印接入点的IP地址
}

void loop()
{
    // put your main code here, to run repeatedly:
}
