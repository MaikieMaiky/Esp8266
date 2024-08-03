#include <Arduino.h>
#include <LittleFS.h>
#include "main.h"

String filename = "/B-maker/note2.txt"; // File name

String foldername = "/B-maker"; // Folder name

void setup()
{
    Serial.begin(9600);
    Serial.println("");

    // Start LittleFS
    if (LittleFS.begin())
    {
        Serial.println("LittleFS Started");
    }
    else
    {
        Serial.println("LittleFS Failed to Start");
    }

    File dataFile = LittleFS.open(filename, "w"); // Open file for writing
    dataFile.println("Hello, B-maker");           // Write to file
    dataFile.close();                             // Close file

    // show the name and size of files in folder
    Dir dir = LittleFS.openDir(foldername); // create directory object
    while (dir.next())                      // detect if there is a next file in the folder
    {
        Serial.print("File: ");
        Serial.print(dir.fileName());
        Serial.print(" Size: ");
        Serial.println(dir.fileSize());
    }
}


void loop()
{
    // put your main code here, to run repeatedly:
}
