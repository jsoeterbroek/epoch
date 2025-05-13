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
#include "display_utils.h"
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
#define INTERVAL_SETUP 30000
uint32_t _timeoutSETUP = millis();
#define INTERVAL_BTN 100  // 1/10 of a second
uint32_t _timeoutBTN = millis();
#define INTERVAL_MS 30000  // seconds
uint32_t _timeoutMS = millis();

// time
rtc_time_t RTCtime;
rtc_date_t RTCdate;

void drawPrefCal(int _cursor) {

  M5.EPD.Clear(true);
  canvas.createCanvas(960, 540);
  canvas.fillCanvas(0);
  canvas.setFreeFont(&Orbitron_Medium_25);

  // Rectangle/grid layout parameters
  const int cols = 3;
  const int rows = 8;
  const int rect_w = 296;
  const int rect_h = 56;
  const int x0 = 30;
  const int y0 = 30;
  const int xgap = 0;
  const int ygap = 0;

  for (int i = 0; i < 24; ++i) {
    int col = i / rows;
    int row = i % rows;
    int x = x0 + col * (rect_w + xgap);
    int y = y0 + row * (rect_h + ygap);

    if (_cursor == i) {
      canvas.setTextColor(TFT_LIGHTGREY);
      canvas.fillRect(x, y, rect_w, rect_h, TFT_DARKGREY);
    } else {
      canvas.setTextColor(TFT_DARKGREY);
      canvas.fillRect(x, y, rect_w, rect_h, TFT_LIGHTGREY);
    }
    canvas.drawString(calendar::calendar_name(i), x + 14, y + 14);
  }

  // push canvas
  canvas.pushCanvas(0, 0, UPDATE_MODE_DU);
}

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

  canvas.drawString(software, 20, 20);
  canvas.setFreeFont(&Orbitron_Medium_25);
  canvas.drawString(maker, 20, 120);
  canvas.drawString(maker_email, 20, 160);
  canvas.drawString(code, 20, 200);
  canvas.drawString(license, 20, 240);
  canvas.pushCanvas(0, 0, UPDATE_MODE_GL16);
  delay(20000);
}

void drawMain() {

  M5.EPD.Clear(true);
  M5.SHT30.UpdateData();
  //temp = M5.SHT30.GetTemperature();
  //hum = M5.SHT30.GetRelHumidity();
  canvas.createCanvas(960, 540);
  canvas.fillCanvas(0);
  canvas.setFreeFont(&Orbitron_Bold_66);

  M5.RTC.getTime(&RTCtime);
  char timeStrbuff[44];
  sprintf(timeStrbuff, "%02d:%02d", RTCtime.hour, RTCtime.min);

  // get current JD date from RTC
  M5.RTC.getDate(&RTCdate);
  double jd = gregorian_to_jd(RTCdate.year, RTCdate.mon, RTCdate.day);

  // get desired calendar to display from Preferences storage
  int c = get_pspref_calendar();
  String calendar = calendar::calendar_name(c);
  Serial.print("DEBUG: draw main screen with calendar: ");  // FIXME, remove later
  Serial.println(calendar);                                 // FIXME, remove later

  String format_weekday = "none";
  String format_weekday_name = "none";
  String format_day = "none";
  String format_month = "none";
  String format_month_description = "none";
  String format_date = "none";
  String format_year = "none";
  String format_day_month = "none";
  String format_day_month_year = "none";
  switch (c) {
    case 0:  // 0 - babylonian
      format_weekday = format_babylonian_date_weekday(jd).c_str();
      format_date = format_babylonian_date(jd).c_str();
      format_year = format_babylonian_date_year(jd).c_str();
      canvas.drawJpgFile(SD, "/back_babylonian.jpg");
      break;
    case 1:  // 1 - gregorian
      format_weekday = format_gregorian_date_weekday(jd).c_str();
      format_day = format_gregorian_date_day(jd).c_str();
      format_month = format_gregorian_date_month(jd).c_str();
      format_year = format_gregorian_date_year(jd).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_gregorian.jpg");
      break;
    case 2:  // 2 - julian
      format_weekday = format_julian_date_weekday(jd).c_str();
      format_day = format_julian_date_day(jd).c_str();
      format_month = format_julian_date_month(jd).c_str();
      format_year = format_julian_date_year(jd).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_julian.jpg");
      break;
    case 3:  // 3 - hebrew
      format_weekday = format_hebrew_date_weekday(jd).c_str();
      format_day = format_hebrew_date_day(jd).c_str();
      format_month = format_hebrew_date_month(jd).c_str();
      format_year = format_hebrew_date_year(jd).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_hebrew.jpg");
      break;
    case 4:  // 4 - islamic
      format_weekday = format_islamic_date_weekday_local(jd, false).c_str();
      format_day = format_islamic_date_day_local(jd, false).c_str();
      format_month = format_islamic_date_month_local(jd, false).c_str();
      format_year = format_islamic_date_year_local(jd, false).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_islamic.jpg");
      break;
    case 5:  // 5 - egyptian
      format_weekday = format_egyptian_date_weekday(jd).c_str();
      format_day = format_egyptian_date_day(jd).c_str();
      format_month = format_egyptian_date_month(jd).c_str();
      format_year = format_egyptian_date_year(jd).c_str();
      //format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_egyptian.jpg");
      break;
    case 6:  // coptic       //  6
      format_weekday = "Coptic Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_coptic.jpg");
      break;
    case 7:  // mayan        //  7
      format_day = format_mayan_date_day(jd).c_str();
      format_month = format_mayan_date_month(jd).c_str();
      format_year = format_mayan_date_long(jd).c_str();
      canvas.drawJpgFile(SD, "/back_mayan.jpg");
      break;
    case 8:  // persian      //  8
      format_weekday = "Persian Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_persian.jpg");
      break;
    case 9:  // french_rev   //  9
      format_weekday = format_french_date_weekday(jd).c_str();
      format_day_month_year = format_french_date_local(jd).c_str();
      canvas.drawJpgFile(SD, "/back_french.jpg");
      break;
    case 10:  // saka        // 10
      format_weekday = format_saka_date_weekday(jd, false).c_str();
      format_day_month_year = format_saka_date_local(jd, false).c_str();
      canvas.drawJpgFile(SD, "/back_saka.jpg");
      break;
    case 11:  // icelandic   // 11
      format_weekday = format_icelandic_date_weekday(jd).c_str();
      format_day = format_icelandic_date_day(jd).c_str();
      format_month = format_icelandic_date_month(jd).c_str();
      format_month_description = format_icelandic_date_month_description(jd).c_str();
      //format_year = format_icelandic_date_year(jd).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_icelandic.jpg");
      break;
    case 12:  // 12 - Julian Anglosaxon
      format_weekday = format_anglosaxon_date_weekday(jd).c_str();
      format_day = format_anglosaxon_date_day(jd).c_str();
      format_month = format_anglosaxon_date_month(jd).c_str();
      format_month_description = format_anglosaxon_date_month_description(jd).c_str();
      //format_year = format_anglosaxon_date_year(jd).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_anglosaxon.jpg");
      break;
    case 13:  // old high german // 13
      format_weekday = format_oldhighgerman_date_weekday(jd).c_str();
      format_day = format_oldhighgerman_date_day(jd).c_str();
      format_month = format_oldhighgerman_date_month(jd).c_str();
      format_month_description = format_oldhighgerman_date_month_description(jd).c_str();
      //format_year = format_oldhighgerman_date_year(jd).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_german.jpg");
      break;
    case 14:  // armenian    // 14
      format_weekday = "Armenian Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_armenian.jpg");
      break;
    case 15:  // georgian    // 15
      format_weekday = "Georgian Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_georgian.jpg");
      break;
    case 16:  // mandaean    // 16
      format_weekday = "Mandaean Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_mandaean.jpg");
      break;
    case 17:  // chinese     // 17
      format_weekday = format_chinese_zodiac_date_weekday(jd).c_str();
      format_day = chinese_day_stem_branch(jd).c_str();
      format_month = chinese_lunar_month_name(jd).c_str();
      format_year = format_chinese_zodiac_date_year(jd).c_str();
      format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_chinese.jpg");
      break;
    case 18:  // buddhist"   // 18
      format_weekday = "Buddhist Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_buddhist.jpg");
      break;
    case 19:  // mongolian   // 19
      format_weekday = "Mongolian Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_mongolian.jpg");
      break;
    case 20:  // ethiopian   // 20
      format_weekday = "Ethiopian Calendar";
      format_day_month_year = "Not yet implemented";
      canvas.drawJpgFile(SD, "/back_ethiopian.jpg");
      break;
    case 21:  // zoroastrian // 21
      format_weekday = format_zoroastrian_date_1(jd, ZoroastrianCalendarVariant::Fasli);
      format_day_month_year = format_zoroastrian_date_2(jd, ZoroastrianCalendarVariant::Fasli);
      canvas.drawJpgFile(SD, "/back_zoroastrian.jpg");
      break;
    case 22:  // hindu  // 22
      format_weekday = format_hindu_date_weekday(jd).c_str();
      format_day = format_hindu_date_day(jd).c_str();
      format_month = format_hindu_date_month(jd).c_str();
      format_year = format_hindu_date_year(jd).c_str();
      //format_day_month = format_day + " " + format_month;
      canvas.drawJpgFile(SD, "/back_hindu.jpg");
      break;
    case 23:  // darian  // 23
      int darian_year, darian_month, sol;
      jd_to_darian(jd, darian_year, darian_month, sol);
      format_weekday = format_darian_date_weekday(darian_year, darian_month, sol, DarianWeekStyle::Latin).c_str();
      format_day_month_year = format_darian_date(darian_year, darian_month, sol, DarianMonthStyle::Mythological).c_str();
      canvas.drawJpgFile(SD, "/back_mars.jpg");
      break;
    default:
      format_weekday = "unknown";
      format_day = "unknown";
      format_month = "unknown";
      format_year = "unknown";
      break;
  }

  // main screen
  canvas.setFreeFont(&Orbitron_Bold_66);
  canvas.drawString(timeStrbuff, 36, 50);
  if (format_weekday != "none") {
    canvas.drawString(format_weekday, 36, 150);
  }
  if (format_day_month_year != "none") {
    canvas.drawString(format_day_month_year, 36, 230);
  } else {
    if (format_day_month != "none") {
      canvas.drawString(format_day_month, 36, 230);
      if (format_year != "none") {
        canvas.drawString(format_year, 36, 310);
      }
      if (format_month_description != "none") {
        canvas.setFreeFont(&Orbitron_Medium_25);
        canvas.drawString(format_month_description, 36, 400);
      }
    } else {
      canvas.drawString(format_day, 36, 230);
      canvas.drawString(format_month, 36, 310);
      if (format_year != "none") {
        canvas.drawString(format_year, 36, 390);
      }
      if (format_month_description != "none") {
        canvas.setFreeFont(&Orbitron_Medium_25);
        canvas.drawString(format_month_description, 36, 400);
      }
    }
  }

  // bottom screen
  canvas.setFreeFont(&Orbitron_Medium_20);
  String cur_calendar = calendar::calendar_name(c);
  String mycal = cur_calendar + " calendar";
  String mytz = ("Timezone: ") + get_timezone();
  canvas.drawString(mycal, 12, 508);
  canvas.drawString(mytz, 320, 508);
  uint32_t batVoltage = readBatteryVoltage();
  uint32_t batPercent = calcBatPercent(batVoltage, MIN_BATTERY_VOLTAGE, MAX_BATTERY_VOLTAGE);
  char buffer[16];
  sprintf(buffer, "%d", batPercent);
  String mybatP = String(buffer);
  String mybat = "Battery: " + mybatP + "%";
  canvas.drawString(mybat, 780, 508);
  canvas.pushCanvas(0, 0, UPDATE_MODE_GL16);
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

  int drawMode = 0;
  // M5EPD::begin(touchEnable, SDEnable, SerialEnable, BatteryADCEnable, I2CEnable)
  M5.begin(false, true, true, true, false);
  M5.EPD.SetRotation(rotation);
  M5.EPD.Clear(true);
  M5.RTC.begin();
  M5.SHT30.Begin();

  // Set Calendar to Preferences
  // set gregorian (1) as default
  // set_pspref_calendar(0);
  //set_pspref_calendar(1);

  drawSplash();

  while (drawMode == 0) {
    if (drawMode == 0) {
      int cursor = get_pspref_calendar();
      if (millis() - _timeoutSETUP > INTERVAL_SETUP) {
        _timeoutSETUP = millis();
        drawPrefCal(cursor);
      }

      // buttons
      M5.update();  // Need to add M5.update() to read the state of the button
      if (M5.BtnR.wasPressed()) {
        cursor = get_pspref_calendar();
        cursor = cursor - 1;
        if (cursor < 0) {
          cursor = 23;
        }
        set_pspref_calendar(cursor);
        drawPrefCal(cursor);
        Serial.print("DEBUG: cursor: ");
        Serial.println(cursor);
      }
      if (M5.BtnP.wasPressed()) {
        Serial.println("Btn P Pressed, drawMode = 1");
        drawMode = 1;
      }
      if (M5.BtnL.wasPressed()) {
        cursor = get_pspref_calendar();
        cursor = cursor + 1;
        if (cursor > 23) {
          cursor = 0;
        }
        set_pspref_calendar(cursor);
        drawPrefCal(cursor);
        Serial.print("DEBUG: cursor: ");
        Serial.println(cursor);
      }
    }
  }

  M5.EPD.Clear(true);
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
  canvas.drawJpgFile(SD, "/back_blank.jpg");

  //WIFI_OFF
  canvas.drawString("Turn WiFi off", 50, 210);
  WiFi.mode(WIFI_OFF);
  delay(1);
  canvas.drawString("Setup finished.", 50, 250);
  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
}

void loop() {

  if (millis() - _timeoutBTN > INTERVAL_BTN) {
    _timeoutBTN = millis();

    // buttons
    M5.update();  // Need to add M5.update() to read the state of the button
    if (M5.BtnR.wasPressed()) {
      int c = get_pspref_calendar();
      c = c - 1;
      if (c < 0) {
        c = 23;
      }
      set_pspref_calendar(c);
      c = get_pspref_calendar();
      String calendar = calendar::calendar_name(c);
      Serial.print("calendar is now: ");
      Serial.println(calendar);
      drawMain();
    }
    if (M5.BtnP.wasPressed()) {
      M5.shutdown();  // FIXME, remove later, needs to be chaged to config screen
      Serial.println("Btn P Pressed; to be used for config screen");
    }
    if (M5.BtnL.wasPressed()) {
      int c = get_pspref_calendar();
      c = c + 1;
      if (c > 23) {
        c = 0;
      }
      set_pspref_calendar(c);
      c = get_pspref_calendar();
      String calendar = calendar::calendar_name(c);
      Serial.print("calendar is now: ");
      Serial.println(calendar);
      drawMain();
    }
  }

  if (millis() - _timeoutMS > INTERVAL_MS) {
    _timeoutMS = millis();
    drawMain();
    //serialTest();
  }
}
