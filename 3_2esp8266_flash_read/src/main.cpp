#include <Arduino.h>
#include <LittleFS.h>
#include "main.h"

String file_name = "/B-maker/notes.txt";

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

    // 确认闪存中是否有file_name文件
    if (LittleFS.exists(file_name))
    {
        Serial.print(file_name);
        Serial.println(" FOUND.");
    }
    else
    {
        Serial.print(file_name);
        Serial.print(" NOT FOUND.");
    }

    // 建立File对象用于从LittleFS中读取文件
    File dataFile = LittleFS.open(file_name, "r");

    // 读取文件内容并且通过串口监视器输出文件信息
    for(size_t i = 0; i < dataFile.size(); i++)
    {
        Serial.write((char)dataFile.read());
    }

    // 完成文件读取后关闭文件
    dataFile.close();
}

void loop()
{
    // put your main code here, to run repeatedly:
}
