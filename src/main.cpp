#include <M5EPD.h>
#include <common.h>
#include <astro.h>
#include <calendar.h>
#include <WiFi.h>
#include <HTTPClient.h>
//#include "NotoSansBold15.h"
//#include "bigFont.h"
//#include "secFont.h"
//#include "smallFont.h"
#include <serialTest.h>

#include <Arduino.h>

M5EPD_Canvas canvas(&M5.EPD);

void drawMain() {


}

void setup() {

    M5.begin();
    M5.EPD.SetRotation(90);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    M5.SHT30.Begin();
    canvas.createCanvas(540, 960);
    Serial.begin(115200);

}

void loop() {
    serialTest();
    drawMain();
    delay(100);
}