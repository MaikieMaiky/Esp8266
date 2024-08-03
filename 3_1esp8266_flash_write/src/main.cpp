#include <Arduino.h>
#include <LittleFS.h> // LittleFS的替代品，LittleFS已经被弃用
#include "main.h"


// LittleFS -- serial peripheral interface flash file system

String file_name = "/B-maker/notes.txt";


void setup()
{
    Serial.begin(9600);
    Serial.println("");

    Serial.println("LittleFS format start");

    /* 新知识 */
    LittleFS.format(); 
    Serial.println("LittleFS format finish");

    if (LittleFS.begin()) // 启动LittleFS
    {
        Serial.println("LittleFS mount success");
    }
    else
    {
        Serial.println("LittleFS mount failed");
    }

    File datafile = LittleFS.open(file_name, "w"); // 建立File对象用于向LittleFS中的file对象（即/notes.txt）写入信息
    datafile.println("Hello, B-Maker!");         // 向datafile写入信息
    datafile.close();                            // 关闭datafile
    Serial.println("Finish Writing data to LittleFS");
}

void loop()
{
    // put your main code here, to run repeatedly:
}
