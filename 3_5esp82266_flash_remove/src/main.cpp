#include <Arduino.h>
#include <LittleFS.h>
#include "main.h"

String filename = "/B-maker/note2.txt"; // 被读取的文件位置和名称

void setup()
{
    Serial.begin(9600);
    Serial.println("");

    if (LittleFS.begin())
    { // 启动闪存文件系统
        Serial.println("LittleFS Started.");
    }
    else
    {
        Serial.println("LittleFS Failed to Start.");
    }

    // 从闪存中删除file_name文件
    if (LittleFS.remove(filename))
    {

        Serial.print(filename);
        Serial.println(" remove sucess");
    }
    else
    {
        Serial.print(filename);
        Serial.println(" remove fail");
    }
}

void loop()
{

}