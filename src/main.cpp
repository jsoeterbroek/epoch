/* main.cpp for Epoch 
 * Copyright (C) 2025  Joost Soeterbroek 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <M5EPD.h>
#include "config.h"
#include "PSpref.h"
#include "_strftime.h"
#include "_locale.h"
#include "datetime.h"
#include "astro.h"
#include "calendar.h"
#include <WiFiManager.h>
#include <HTTPClient.h>
#include "Orbitron_Medium_20.h"
#include "Orbitron44.h"
#include "serialTest.h"

#include <Arduino.h>

M5EPD_Canvas canvas(&M5.EPD);

char temStr[10];
char humStr[10];

float temHere;
float humHere;

rtc_time_t RTCtime;
rtc_date_t RTCdate;

void drawMain() {

    M5.EPD.Clear(true);
    M5.SHT30.UpdateData();
    temHere = M5.SHT30.GetTemperature();
    humHere = M5.SHT30.GetRelHumidity();
    canvas.createCanvas(960, 540);
    canvas.fillCanvas(0);
    canvas.setFreeFont(&Orbitron_Bold_66);
    canvas.drawString(String(temHere).substring(0, 4), 100, 140);
    canvas.setFreeFont(&Orbitron_Bold_66);
    canvas.drawString(String((int)humHere), 100, 220);
    canvas.pushCanvas(0, 0, UPDATE_MODE_A2);    
}

void configModeCallback(WiFiManager *myWiFiManager) {

    Serial.println("******************");
    Serial.println(TXT_WM_WEBPORTAL_STARTED);
    Serial.println(WiFi.softAPIP().toString());
    Serial.println(TXT_WM_CONNECT_SSID);
    Serial.println(myWiFiManager->getConfigPortalSSID());
    Serial.println(TXT_WM_WITH_PASSWORD);
    Serial.println(TXT_WM_CONFIG_DEVICE);
    Serial.println("******************");

}

void setup() {

    M5.begin();
    M5.EPD.SetRotation(180);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    M5.SHT30.Begin();
    canvas.createCanvas(960, 540);
    Serial.begin(115200);

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    //wm.resetSettings();

    bool res;
    wm.setConfigPortalTimeout(5000);
    wm.setAPCallback(configModeCallback);
    res = wm.autoConnect(wifi_mngr_networkname, wifi_mngr_password);

    if (!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }

    // set NTP time
    struct tm timeinfo;
    initTime(TIMEZONE);
    delay(100);
    while (!getLocalTime(&timeinfo, 1000)) {
        Serial.print('.');
    };
    Serial.println("OK: obtained time");
    Serial.println(&timeinfo, " %A, %B %d %Y %H:%M:%S");

    Serial.println("set rtc clock from NTP");
    char UPDATE_TIME[50];  
    char TIME_HOUR[5];  
    char TIME_MIN[5];  
    char TIME_SEC[5];  
    strftime(UPDATE_TIME, sizeof(UPDATE_TIME), "%T", &timeinfo);  // extract just the 'time' portion
    strftime(TIME_HOUR, sizeof(TIME_HOUR), "%H", &timeinfo); 
    strftime(TIME_MIN, sizeof(TIME_MIN), "%M", &timeinfo); 
    strftime(TIME_SEC, sizeof(TIME_SEC), "%S", &timeinfo);
    Serial.println(UPDATE_TIME);
    RTCtime.hour = atoi(TIME_HOUR);
    RTCtime.min = atoi(TIME_MIN);
    RTCtime.sec = atoi(TIME_SEC);
    M5.RTC.setTime(&RTCtime);
    char DATE_DAY_WEEK[5];  
    char DATE_DAY_MONTH[5];  
    char DATE_MONTH[5];  
    char DATE_YEAR[5];  
    strftime(DATE_DAY_MONTH, sizeof(DATE_DAY_MONTH), "%d", &timeinfo); 
    strftime(DATE_MONTH, sizeof(DATE_MONTH), "%m", &timeinfo); 
    strftime(DATE_YEAR, sizeof(DATE_YEAR), "%Y", &timeinfo);
    RTCdate.day = atoi(DATE_DAY_MONTH);
    RTCdate.mon = atoi(DATE_MONTH);
    RTCdate.year = atoi(DATE_YEAR);
    M5.RTC.setDate(&RTCdate);


    // Set Calendar to Preferences
    // set gregorian as default



    canvas.useFreetypeFont(false);
    canvas.setFreeFont(&Orbitron_Medium_25);
    //canvas.drawJpgFile(SD, "/back.jpg");
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16 );
}

void loop() {
    

    // Get Calendar from Preferences

    delay(100);
    drawMain();
    delay(700);
    M5.shutdown(600);

    serialTest();
}
