// https://github.com/VolosR/WeatherM5Paper/blob/main/Weather/Weather.ino
#include <M5EPD.h>
#include <common.h>
#include <astro.h>
#include <calendar.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "Orbitron_Medium_20.h"
#include "Orbitron44.h"
#include <serialTest.h>

#include <Arduino.h>

M5EPD_Canvas canvas(&M5.EPD);

char temStr[10];
char humStr[10];

float temHere;
float humHere;

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

void drawMain() {

    M5.EPD.Clear(true);
    M5.SHT30.UpdateData();
    temHere = M5.SHT30.GetTemperature();
    humHere = M5.SHT30.GetRelHumidity();
    canvas.setFreeFont(&Orbitron_Bold_66);
    canvas.drawString(String(temHere).substring(0,4),100,140);
    canvas.setFreeFont(&Orbitron_Bold_66);
    canvas.drawString(String((int)humHere),100,220);
    canvas.pushCanvas(0,0,UPDATE_MODE_A2  );    
}

void setup() {

    M5.begin();
    M5.EPD.SetRotation(180);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    M5.SHT30.Begin();
    canvas.createCanvas(960, 540);
    Serial.begin(115200);

    canvas.useFreetypeFont(false);
    canvas.setFreeFont(&Orbitron_Medium_25);
    //canvas.drawJpgFile(SD, "/back.jpg");
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16 );
}

void loop() {
    delay(100);
    drawMain();
    delay(700);
    M5.shutdown(600);

    serialTest();
}
