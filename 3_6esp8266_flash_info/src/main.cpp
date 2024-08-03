#include "main.h"
#include <Arduino.h>
#include <LittleFS.h>

// 作业完成嘿嘿嘿

FSInfo fs_info;

void setup()
{
    Serial.begin(9600);

    if (LittleFS.begin())
    {
        Serial.println("LittleFS Started");
    }
    else
    {
        Serial.println("Error: LittleFS failed to start");
    }

    /* new knowwledge */
    // Get the file system information
    LittleFS.info(fs_info);

    // total accessable space( in bytes )
    Serial.printf("Total space: %u bytes\n", fs_info.totalBytes);

    // total space used( in bytes )
    Serial.printf("Used space: %u bytes\n", fs_info.usedBytes);

    // max path length (contain path and '\0' at the end)
    Serial.printf("Max path length: %u\n", fs_info.maxPathLength);

    // max open files at the same time
    Serial.printf("Max open files: %u\n", fs_info.maxOpenFiles);

    // block size of the file system
    Serial.printf("Block size: %u\n", fs_info.blockSize);

    // page size of the file system
    Serial.printf("Page size: %u\n", fs_info.pageSize);
}

void loop()
{
    // put your main code here, to run repeatedly:
}
