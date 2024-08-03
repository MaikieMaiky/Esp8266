#include "main.h"
#include <Arduino.h>
#include <LittleFS.h>

// 本章节通过append向文件中追加数据
// 补充一下,关于LittleFS的配置,需要在platformio.ini中添加

String filename = "/B-maker/notes.txt";

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
    if (LittleFS.exists(filename))
    {

        Serial.print(filename);
        Serial.println(" FOUND.");

        File dataFile = LittleFS.open(filename, "a"); // 建立File对象用于向LittleFS中的file对象（即/notes.txt）写入信息
        dataFile.println("This is Appended Info.");  // 向dataFile添加字符串信息
        dataFile.close();                            // 完成文件操作后关闭文件
        Serial.println("Finished Appending data to LittleFS");

        // 读取文件中的信息
        File dataFileRead = LittleFS.open(filename, "r");
        if (dataFileRead)
        {
            Serial.print(filename);
            Serial.println(" Found.");
            Serial.print("File Content: ");
            while (dataFileRead.available())
            {
                Serial.write(dataFileRead.read());
            }
            dataFileRead.close();
        }
        else
        {
            Serial.print(filename);
            Serial.println(" NOT FOUND.");
        }
    }
    else
    {
        Serial.print(filename);
        Serial.print(" NOT FOUND.");
    }
}

void loop()
{
    // put your main code here, to run repeatedly:
}
