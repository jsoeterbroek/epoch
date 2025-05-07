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
#include "globals.h"
#include "config.h"
#include "PSpref.h"
#include "_strftime.h"
#include "_locale.h"
#include "datetime.h"
#include "astro.h"
#include "calendar.h"
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include "Orbitron_Medium_20.h"
#include "Orbitron44.h"
#include "calibri22LatinFont.h"
#include "serialTest.h"

#include <Arduino.h>

#include <FS.h>
#include <SPI.h>
#include <JPEGDecoder.h>

M5EPD_Canvas canvas(&M5.EPD);

// touch
uint16_t rotation = 180;
int point[2][2];

// Time intervals for buttons, screens
//
// set INTERVAL to 0 if you want it to fire 
// immediately the first time
#define INTERVAL_BTN 100 // 1/10 of a second
uint32_t _timeoutBTN = millis(); 
#define INTERVAL_MS 30000 // seconds
uint32_t _timeoutMS = millis(); 


char temStr[10];
char humStr[10];
float temp;
float hum;

// time
rtc_time_t RTCtime;
rtc_date_t RTCdate;

void drawSplash() {

    M5.EPD.Clear(true);
    canvas.createCanvas(960, 540);
    canvas.fillCanvas(0);
    canvas.setFreeFont(&Orbitron_Bold_66);
    String software = "EPOCH ";
    software += String("v") + epoch_version_major() + "." + epoch_version_minor() + "." + epoch_version_patch();
    String maker = "Copyright (C) 2025 Joost Soeterbroek";
    String maker_email = "<joost.soeterbroek@gmail.com>";
    String code = "https://github.com/jsoeterbroek/epoch";
    String aknowledgements = "Aknowledgements: see file AKNOWLEDGEMENTS.txt";
    String license = "GNU GENERAL PUBLIC LICENSE, Version 3";

    canvas.drawString(software ,20, 20);
    canvas.setFreeFont(&Orbitron_Medium_25);
    canvas.drawString(maker ,20, 120);
    canvas.drawString(maker_email, 20, 160);
    canvas.drawString(code, 20, 200);
    canvas.drawString(license, 20, 240);
    canvas.pushCanvas(0, 0, UPDATE_MODE_GL16);
    delay(20000);
}

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
    canvas.drawString(timeStrbuff, 10, 20);

    // get JD from RTC
    double jd = gregorian_to_jd(RTCdate.year, RTCdate.mon, RTCdate.day);

    // get desired calendar to display from Preferences storage
    int c = get_pspref_calendar();
    String calendar = calendar::calendar_name(c);
    Serial.print("DEBUG: draw main screen with calendar: "); // FIXME, remove later
    Serial.println(calendar); // FIXME, remove later

    String format_weekday;
    String format_day;
    String format_month;
    String format_year;
    String format_day_month_year;
    switch (c) {
        case 0: // 0 - babylonian
            format_weekday = "Babylonian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 1: // 1 - gregorian
            format_weekday = format_gregorian_date_weekday(jd).c_str();
            format_day = format_gregorian_date_day(jd).c_str();
            format_month = format_gregorian_date_month(jd).c_str();
            format_year = format_gregorian_date_year(jd).c_str();
            format_day_month_year = format_day + " " + format_month + " " + format_year;
            break;
        case 2: // 2 - julian
            format_weekday = format_julian_date_weekday(jd).c_str();
            format_day = format_julian_date_day(jd).c_str();
            format_month = format_julian_date_month(jd).c_str();
            format_year = format_julian_date_year(jd).c_str();
            format_day_month_year = format_day + " " + format_month + " " + format_year;
            break;
        case 3: // 3 - hebrew
            format_weekday = "Hebrew Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 4: // 4 - islamic
            format_weekday = format_islamic_date_weekday(jd, false).c_str();
            format_day_month_year = format_islamic_date_local(jd, false).c_str();
            break;
        case 5: // 5 - egyptian 
            format_weekday = "Old Egyptian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 6: // coptic       //  6
            format_weekday = "Coptic Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 7: // mayan        //  7
            format_weekday = "Mayan Long Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 8: // persian      //  8
            format_weekday = "Persian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 9: // french_rev   //  9
            format_weekday = "French (Rev) Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 10: // saka        // 10
            format_weekday = "Saka Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 11: // icelandic   // 11
            format_weekday = "Icelandic Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 12: // 12 - Julian Anglosaxon
            format_weekday = format_anglosaxon_date_weekday(jd).c_str();
            format_day_month_year = format_anglosaxon_date_local(jd).c_str();
            break;
        case 13: // old high german // 13
            format_weekday = format_oldhighgerman_date_weekday(jd).c_str();
            format_day_month_year = format_oldhighgerman_date_local(jd).c_str();
            break;
        case 14: // armenian    // 14
            format_weekday = "Armenian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 15: // georgian    // 15
            format_weekday = "Georgian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 16: // mandaean    // 16
            format_weekday = "Mandaean Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 17: // chinese     // 17
            format_weekday = "Chinese Zodiac Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 18: // buddhist"   // 18
            format_weekday = "Buddhist Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 19: // mongolian   // 19
            format_weekday = "Mongolian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 20: // ethiopian   // 20
            format_weekday = "Ethiopian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 21: // zoroastrian // 21
            format_weekday = "Zoroastrian Calendar";
            format_day_month_year = "Not yet implemented";
            break;
        case 22: // darian  // 22
            int darian_year, darian_month, sol;
            jd_to_darian(jd, darian_year, darian_month, sol);
            format_weekday = darian_weekday_string(darian_year, darian_month, sol, DarianWeekStyle::Latin).c_str();
            format_day_month_year = darian_date_string(darian_year, darian_month, sol, DarianMonthStyle::Mythological).c_str();
            break;
        default:
            format_weekday = "unknown";
            format_day = "unknown";
            format_month = "unknown";
            format_year = "unknown";
            break;
    }

    canvas.setFreeFont(&Orbitron_Bold_66);
    canvas.drawString(format_weekday, 10, 140);
    canvas.drawString(format_day_month_year, 10, 240);

    canvas.setFreeFont(&Orbitron_Medium_20);
    String cur_calendar = calendar::calendar_name(c);
    String mycal = ("Calendar: ") + cur_calendar;
    String mytz = ("Timezone: ") + get_timezone();
    canvas.drawString(mycal, 12, 508);
    canvas.drawString(mytz, 300, 508);

    //canvas.drawString(String(temp).substring(0, 4), 10, 386);
    //canvas.drawString(String((int)hum), 10, 460);
    canvas.pushCanvas(0, 0, UPDATE_MODE_GL16);
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

    // M5EPD::begin(touchEnable, SDEnable, SerialEnable, BatteryADCEnable, I2CEnable)
    M5.begin(false, true, true, true, false);
    M5.EPD.SetRotation(rotation);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    M5.SHT30.Begin();

    // Set Calendar to Preferences
    // set gregorian (1) as default
    // set_pspref_calendar(0);
    set_pspref_calendar(1);

    drawSplash();
    canvas.createCanvas(960, 540);
    canvas.fillCanvas(0);
    Serial.begin(115200);

    canvas.setFreeFont(&Orbitron_Medium_25);
    canvas.drawString("starting WiFiManager", 50, 50);

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
        Serial.println("WiFi failed to connect");
        canvas.drawString("WiFi failed to connect", 50, 90);
        // ESP.restart();
    } else {
        //if you get here you have connected to the WiFi    
        Serial.println("WiFi connected");
        canvas.drawString("WiFi connected", 50, 90);
    }

    // set NTP time
    canvas.drawString("Get time from Internet NTP", 50, 130);
    struct tm timeinfo;
    initTime(TIMEZONE);
    delay(100);
    while (!getLocalTime(&timeinfo, 1000)) {
        Serial.print('.');
    };
    Serial.println("OK: obtained time");
    Serial.println(&timeinfo, " %A, %B %d %Y %H:%M:%S");
    canvas.drawString("OK: obtained current time, date", 50, 170);

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

    //WIFI_OFF
    canvas.drawString("Turn WiFi off", 50, 210);
    WiFi.mode(WIFI_OFF);
    delay(1);
    canvas.drawString("Setup finished.", 50, 250);
}

void loop() {
    
    if(millis()-_timeoutBTN > INTERVAL_BTN) {
        _timeoutBTN = millis();

        // buttons
        M5.update(); // Need to add M5.update() to read the state of the button
        if (M5.BtnR.wasPressed()) {
            int c = get_pspref_calendar();
            c = c - 1;
            if (c < 0) c = 22;
            set_pspref_calendar(c);
            c = get_pspref_calendar();
            String calendar = calendar::calendar_name(c);
            Serial.print("calendar is now: ");
            Serial.println(calendar);
            drawMain();
        }
        if (M5.BtnP.wasPressed()) {
            Serial.println("Btn P Pressed; to be used for config screen");
        }
        if (M5.BtnL.wasPressed()) {
            int c = get_pspref_calendar();
            c = c + 1;
            if (c > 22) c = 0;
            set_pspref_calendar(c);
            c = get_pspref_calendar();
            String calendar = calendar::calendar_name(c);
            Serial.print("calendar is now: ");
            Serial.println(calendar);
            drawMain();
        }
    }

    if(millis()-_timeoutMS > INTERVAL_MS) {
        _timeoutMS = millis();
        drawMain();
    }

    //serialTest();
}