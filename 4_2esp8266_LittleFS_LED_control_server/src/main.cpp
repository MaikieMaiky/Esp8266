/**********************************************************************
使用ESP8266-NodeMCU建立一个有多个页面的网站。在LED页面中配有可控制LED点亮和熄灭的
按钮。点击首页的LED Page链接进入LED页。点击LED页按钮将控制NodeMCU的内置LED点亮和熄灭。
!!! 但是还是有一个问题,当我们电机按钮之后,页面会刷新,这样不太友好,我们可以使用AJAX技术来解决这个问题 !!!
***********************************************************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>      // 本程序使用ESP8266WiFi库
#include <ESP8266WiFiMulti.h> // 本程序使用ESP8266WiFiMulti库
#include <ESP8266WebServer.h> // 本程序使用ESP8266WebServer库
#include <LittleFS.h>         // 本程序使用LittleFS库
#include "main.h"

ESP8266WiFiMulti wifiMulti; // 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'

ESP8266WebServer esp8266_server(80); // 建立网络服务器对象，该对象用于响应HTTP请求。监听端口（80）

void setup()
{
    Serial.begin(9600);
    Serial.println("");

    pinMode(LED_BUILTIN, OUTPUT); // 初始化NodeMCU控制板载LED引脚为OUTPUT

    // 通过addAp函数存储  WiFi名称       WiFi密码
    wifiMulti.addAP("C++", "309309309");                         // 将需要连接的一系列WiFi ID和密码输入这里
    wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2"); // ESP8266-NodeMCU再启动后会扫描当前网络
    wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3"); // 环境查找是否有这里列出的WiFi ID。如果有
    Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。

    int i = 0;
    while (wifiMulti.run() != WL_CONNECTED)
    {                // 在当前环境中搜索addAP函数所存储的WiFi
        delay(1000); // 如果搜到多个存储的WiFi那么NodeMCU
        Serial.print(i++);
        Serial.print('.'); // 将会连接信号最强的那一个WiFi信号。
    }
    
    // WiFi连接成功后将通过串口监视器输出连接成功信息
    Serial.println('\n');           // WiFi连接成功后
    Serial.print("Connected to ");  // NodeMCU将通过串口监视器输出。
    Serial.println(WiFi.SSID());    // 连接的WiFI名称
    Serial.print("IP address:\t");  // 以及
    Serial.println(WiFi.localIP()); // NodeMCU的IP地址

    if (LittleFS.begin())
    { // 启动闪存文件系统
        Serial.println("LittleFS Started.");
    }
    else
    {
        Serial.println("LittleFS Failed to Start.");
    }

    esp8266_server.on("/LED-Control", handleLEDControl); // 告知系统如何处理/LED-Control请求
    esp8266_server.onNotFound(handleUserRequest);        // 告知系统如何处理其它用户请求

    esp8266_server.begin(); // 启动网站服务
    Serial.println("HTTP server started");
}

void loop()
{
    esp8266_server.handleClient(); // 处理用户请求
}

// 处理/LED-Control请求
void handleLEDControl()
{
    bool ledStatus = digitalRead(LED_BUILTIN);                                            // 此变量用于储存LED状态
    ledStatus == HIGH ? digitalWrite(LED_BUILTIN, LOW) : digitalWrite(LED_BUILTIN, HIGH); // 点亮或者熄灭LED

    esp8266_server.sendHeader("Location", "/LED.html");
    esp8266_server.send(303);
}

// 处理用户浏览器的HTTP访问
void handleUserRequest()
{

    // 获取用户请求资源(Request Resource）
    String reqResource = esp8266_server.uri();
    Serial.print("reqResource: ");
    Serial.println(reqResource);

    // 通过handleFileRead函数处处理用户请求资源
    bool fileReadOK = handleFileRead(reqResource);

    // 如果在LittleFS无法找到用户访问的资源，则回复404 (Not Found)
    if (!fileReadOK)
    {
        esp8266_server.send(404, "text/plain", "404 Not Found");
    }
}

bool handleFileRead(String resource)
{ // 处理浏览器HTTP访问

    if (resource.endsWith("/"))
    {                             // 如果访问地址以"/"为结尾
        resource = "/index.html"; // 则将访问地址修改为/index.html便于LittleFS访问
    }

    String contentType = getContentType(resource); // 获取文件类型

    if (LittleFS.exists(resource))
    {                                                 // 如果访问的文件可以在LittleFS中找到
        File file = LittleFS.open(resource, "r");     // 则尝试打开该文件
        esp8266_server.streamFile(file, contentType); // 并且将该文件返回给浏览器
        file.close();                                 // 并且关闭文件
        return true;                                  // 返回true
    }
    return false; // 如果文件未找到，则返回false
}

// 获取文件类型
String getContentType(String filename)
{
    if (filename.endsWith(".htm"))
        return "text/html";
    else if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".png"))
        return "image/png";
    else if (filename.endsWith(".gif"))
        return "image/gif";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    else if (filename.endsWith(".xml"))
        return "text/xml";
    else if (filename.endsWith(".pdf"))
        return "application/x-pdf";
    else if (filename.endsWith(".zip"))
        return "application/x-zip";
    else if (filename.endsWith(".gz"))
        return "application/x-gzip";
    return "text/plain";
}