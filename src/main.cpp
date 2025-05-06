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

float temp;
float hum;

rtc_time_t RTCtime;
rtc_date_t RTCdate;

void drawMain() {

    M5.EPD.Clear(true);
    M5.SHT30.UpdateData();
    temp = M5.SHT30.GetTemperature();
    hum = M5.SHT30.GetRelHumidity();
    canvas.createCanvas(960, 540);
    canvas.fillCanvas(0);
    canvas.setFreeFont(&Orbitron_Bold_66);

    M5.RTC.getTime(&RTCtime);
    char timeStrbuff[44];
    sprintf(timeStrbuff, "%02d:%02d", RTCtime.hour, RTCtime.min);
    canvas.drawString(timeStrbuff, 100, 20);
    M5.RTC.getDate(&RTCdate);
    char dateStrbuff[44];
    canvas.setFreeFont(&Orbitron_Medium_25);
    sprintf(dateStrbuff, "(%02d/%02d/%02d)", RTCdate.day, RTCdate.mon, RTCdate.year);
    canvas.drawString(dateStrbuff, 360, 58);

    double jd = gregorian_to_jd(RTCdate.year, RTCdate.mon, RTCdate.day);
    //double jd = gregorian_to_jd(2025, 5, 2);  // friday, 2th may, 2025 (= 2460797.5)
    //Serial.print("Calculated JD (should be '2460797.5'): ");
    //Serial.println(jd);
    //Serial.println(calendar::format_iso_date(jd).c_str());

    int c = get_pspref_calendar();
    String calendar = calendar::calendar_name(c);
    Serial.print("DEBUG: draw main screen with calendar: "); // FIXME, remove later
    Serial.print(calendar); // FIXME, remove later

    String format_weekday;
    String format_day;
    String format_month;
    String format_year;
    String format_day_month_year;
    switch (c) {
        case 0:
            format_weekday = format_gregorian_date_weekday(jd).c_str();
            format_day = format_gregorian_date_day(jd).c_str();
            format_month = format_gregorian_date_month(jd).c_str();
            format_year = format_gregorian_date_year(jd).c_str();
            break;
        default:
            format_weekday = "unknown";
            format_day = "unknown";
            format_month = "unknown";
            format_year = "unknown";
            break;
    }


    format_day_month_year = format_day + " " + format_month + " " + format_year;
    canvas.setFreeFont(&Orbitron_Bold_66);
    canvas.drawString(format_weekday, 100, 140);
    canvas.drawString(format_day_month_year, 100, 240);

    canvas.drawString(String(temp).substring(0, 4), 100, 340);
    canvas.drawString(String((int)hum), 100, 410);
    canvas.pushCanvas(0, 0, UPDATE_MODE_A2);
}

void configModeCallback(WiFiManager *myWiFiManager) {

    Serial.println("******************");
    Serial.println(TXT_WM_WEBPORTAL_STARTED); Serial.println(WiFi.softAPIP().toString());
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

    // Set Calendar to Preferences
    // set gregorian (0) as default
    set_pspref_calendar(0);

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
