/* Display helper utilities for esp32-weather-epd.
 * Copyright (C) 2022-2025  Luke Marzen
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

#include <cmath>
#include <vector>
#include <M5EPD.h>
#include <Arduino.h>
#include "_locale.h"
#include "_strftime.h"
#include "config.h"
#include "display_utils.h"
//#include "icons/icons_24x24.h"
#include <cstdint>

/* Returns battery voltage in millivolts (mv).
 */
uint32_t readBatteryVoltage() {
  uint32_t batteryVoltage;
  batteryVoltage = M5.getBatteryVoltage();
  return batteryVoltage;
}  // end readBatteryVoltage

/* Returns battery percentage, rounded to the nearest integer.
 * Takes a voltage in millivolts and uses a sigmoidal approximation to find an
 * approximation of the battery life percentage remaining.
 * 
 * This function contains LGPLv3 code from 
 * <https://github.com/rlogiacco/BatterySense>.
 * 
 * Symmetric sigmoidal approximation
 * <https://www.desmos.com/calculator/7m9lu26vpy>
 *
 * c - c / (1 + k*x/v)^3
 */
uint32_t calcBatPercent(uint32_t v, uint32_t minv, uint32_t maxv) {
  // slow
  //uint32_t p = 110 - (110 / (1 + pow(1.468 * (v - minv)/(maxv - minv), 6)));

  // steep
  //uint32_t p = 102 - (102 / (1 + pow(1.621 * (v - minv)/(maxv - minv), 8.1)));

  // normal
  uint32_t p = 105 - (105 / (1 + pow(1.724 * (v - minv) / (maxv - minv), 5.5)));
  return p >= 100 ? 100 : p;
}  // end calcBatPercent

void getRefreshTimeStr(String &s, bool timeSuccess, tm *timeInfo) {
  if (timeSuccess == false) {
    s = TXT_UNKNOWN;
    return;
  }

  char buf[48] = {};
  _strftime(buf, sizeof(buf), REFRESH_TIME_FORMAT, timeInfo);
  s = buf;

  // remove double spaces.
  s.replace("  ", " ");
  return;
}  // end getRefreshTimeStr

/* Returns 24x24 bitmap moon status.
FIXME: fix
const uint8_t *getMoonBitmap24() {
  return wi_moon_full_24x24;
}
*/
String getMoonPng48(String _moonPhase) {

  // if (angle < 7.5 || angle >= 352.5) { //   return "New Moon";
  // if (angle < 22.5) { //   return "Waxing Crescent-1";
  // if (angle < 37.5) { //   return "Waxing Crescent-2";
  // if (angle < 52.5) { //   return "Waxing Crescent-3";
  // if (angle < 67.5) { //   return "Waxing Crescent-4";
  // if (angle < 82.5) { //   return "Waxing Crescent-5";
  // if (angle < 97.5) { //   return "Waxing Crescent-6";
  // if (angle < 112.5) { //   return "First Quarter";
  // if (angle < 127.5) { //   return "Waxing Gibbous-1";
  // if (angle < 142.5) { //   return "Waxing Gibbous-2";
  // if (angle < 157.5) { //   return "Waxing Gibbous-3";
  // if (angle < 172.5) { //   return "Waxing Gibbous-4";
  // if (angle < 187.5) { //   return "Waxing Gibbous-5";
  // if (angle < 202.5) { //   return "Waxing Gibbous-6";
  // if (angle < 217.5) { //   return "Full Moon";
  // if (angle < 232.5) { //   return "Waning Gibbous-1";
  // if (angle < 247.5) { //   return "Waning Gibbous-2";
  // if (angle < 262.5) { //   return "Waning Gibbous-3";
  // if (angle < 277.5) { //   return "Waning Gibbous-4";
  // if (angle < 292.5) { //   return "Waning Gibbous-5";
  // if (angle < 307.5) { //   return "Waning Gibbous-6";
  // if (angle < 322.5) { //   return "Last Quarter";
  // if (angle < 337.5) { //   return "Waning Crescent-1";
  // if (angle < 352.5) { //   return "Waning Crescent-2";
  String moonPng = "/icons/48/wi-moon-alt-";
  if (_moonPhase == "New Moon") {
    moonPng += "new.png";
  } else if (_moonPhase == "Waxing Crescent-1") {
    moonPng += "waxing-crescent-1.png";
  } else if (_moonPhase == "Waxing Crescent-2") {
    moonPng += "waxing-crescent-2.png";
  } else if (_moonPhase == "Waxing Crescent-3") {
    moonPng += "waxing-crescent-3.png";
  } else if (_moonPhase == "Waxing Crescent-4") {
    moonPng += "waxing-crescent-4.png";
  } else if (_moonPhase == "Waxing Crescent-5") {
    moonPng += "waxing-crescent-5.png";
  } else if (_moonPhase == "Waxing Crescent-6") {
    moonPng += "waxing-crescent-6.png";
  } else if (_moonPhase == "First Quarter") {
    moonPng += "first-quarter.png";
  } else if (_moonPhase == "Waxing Gibbous-1") {
    moonPng += "waxing-gibbous-1.png";
  } else if (_moonPhase == "Waxing Gibbous-2") {
    moonPng += "waxing-gibbous-2.png";
  } else if (_moonPhase == "Waxing Gibbous-3") {
    moonPng += "waxing-gibbous-3.png";
  } else if (_moonPhase == "Waxing Gibbous-4") {
    moonPng += "waxing-gibbous-4.png";
  } else if (_moonPhase == "Waxing Gibbous-5") {
    moonPng += "waxing-gibbous-5.png";
  } else if (_moonPhase == "Waxing Gibbous-6") {
    moonPng += "waxing-gibbous-6.png";
  } else if (_moonPhase == "Full Moon") {
    moonPng += "full.png";
  } else if (_moonPhase == "Waning Gibbous-1") {
    moonPng += "waning-gibbous-1.png";
  } else if (_moonPhase == "Waning Gibbous-2") {
    moonPng += "waning-gibbous-2.png";
  } else if (_moonPhase == "Waning Gibbous-3") {
    moonPng += "waning-gibbous-3.png";
  } else if (_moonPhase == "Waning Gibbous-4") {
    moonPng += "waning-gibbous-4.png";
  } else if (_moonPhase == "Waning Gibbous-5") {
    moonPng += "waning-gibbous-5.png";
  } else if (_moonPhase == "Waning Gibbous-6") {
    moonPng += "waning-gibbous-6.png";
  } else if (_moonPhase == "Last Quarter") {
    moonPng += "last-quarter.png";
  } else if (_moonPhase == "Waning Crescent-1") {
    moonPng += "waning-crescent-1.png";
  } else if (_moonPhase == "Waning Crescent-2") {
    moonPng += "waning-crescent-2.png";
  } else if (_moonPhase == "Waning Crescent-3") {
    moonPng += "waning-crescent-3.png";
  } else if (_moonPhase == "Waning Crescent-4") {
    moonPng += "waning-crescent-4.png";
  } else if (_moonPhase == "Waning Crescent-5") {
    moonPng += "waning-crescent-5.png";
  } else if (_moonPhase == "Waning Crescent-6") {
    moonPng += "waning-crescent-6.png";
  } else {
    moonPng = "/icons/48/wi-moon-alt-waning-gibbous-2.png";  // default
  }
  return moonPng;
}

String getMoonPng96(String _moonPhase) {

  // if (angle < 7.5 || angle >= 352.5) { //   return "New Moon";
  // if (angle < 22.5) { //   return "Waxing Crescent-1";
  // if (angle < 37.5) { //   return "Waxing Crescent-2";
  // if (angle < 52.5) { //   return "Waxing Crescent-3";
  // if (angle < 67.5) { //   return "Waxing Crescent-4";
  // if (angle < 82.5) { //   return "Waxing Crescent-5";
  // if (angle < 97.5) { //   return "Waxing Crescent-6";
  // if (angle < 112.5) { //   return "First Quarter";
  // if (angle < 127.5) { //   return "Waxing Gibbous-1";
  // if (angle < 142.5) { //   return "Waxing Gibbous-2";
  // if (angle < 157.5) { //   return "Waxing Gibbous-3";
  // if (angle < 172.5) { //   return "Waxing Gibbous-4";
  // if (angle < 187.5) { //   return "Waxing Gibbous-5";
  // if (angle < 202.5) { //   return "Waxing Gibbous-6";
  // if (angle < 217.5) { //   return "Full Moon";
  // if (angle < 232.5) { //   return "Waning Gibbous-1";
  // if (angle < 247.5) { //   return "Waning Gibbous-2";
  // if (angle < 262.5) { //   return "Waning Gibbous-3";
  // if (angle < 277.5) { //   return "Waning Gibbous-4";
  // if (angle < 292.5) { //   return "Waning Gibbous-5";
  // if (angle < 307.5) { //   return "Waning Gibbous-6";
  // if (angle < 322.5) { //   return "Last Quarter";
  // if (angle < 337.5) { //   return "Waning Crescent-1";
  // if (angle < 352.5) { //   return "Waning Crescent-2";
  String moonPng = "/icons/96/wi-moon-alt-";
  if (_moonPhase == "New Moon") {
    moonPng += "new.png";
  } else if (_moonPhase == "Waxing Crescent-1") {
    moonPng += "waxing-crescent-1.png";
  } else if (_moonPhase == "Waxing Crescent-2") {
    moonPng += "waxing-crescent-2.png";
  } else if (_moonPhase == "Waxing Crescent-3") {
    moonPng += "waxing-crescent-3.png";
  } else if (_moonPhase == "Waxing Crescent-4") {
    moonPng += "waxing-crescent-4.png";
  } else if (_moonPhase == "Waxing Crescent-5") {
    moonPng += "waxing-crescent-5.png";
  } else if (_moonPhase == "Waxing Crescent-6") {
    moonPng += "waxing-crescent-6.png";
  } else if (_moonPhase == "First Quarter") {
    moonPng += "first-quarter.png";
  } else if (_moonPhase == "Waxing Gibbous-1") {
    moonPng += "waxing-gibbous-1.png";
  } else if (_moonPhase == "Waxing Gibbous-2") {
    moonPng += "waxing-gibbous-2.png";
  } else if (_moonPhase == "Waxing Gibbous-3") {
    moonPng += "waxing-gibbous-3.png";
  } else if (_moonPhase == "Waxing Gibbous-4") {
    moonPng += "waxing-gibbous-4.png";
  } else if (_moonPhase == "Waxing Gibbous-5") {
    moonPng += "waxing-gibbous-5.png";
  } else if (_moonPhase == "Waxing Gibbous-6") {
    moonPng += "waxing-gibbous-6.png";
  } else if (_moonPhase == "Full Moon") {
    moonPng += "full.png";
  } else if (_moonPhase == "Waning Gibbous-1") {
    moonPng += "waning-gibbous-1.png";
  } else if (_moonPhase == "Waning Gibbous-2") {
    moonPng += "waning-gibbous-2.png";
  } else if (_moonPhase == "Waning Gibbous-3") {
    moonPng += "waning-gibbous-3.png";
  } else if (_moonPhase == "Waning Gibbous-4") {
    moonPng += "waning-gibbous-4.png";
  } else if (_moonPhase == "Waning Gibbous-5") {
    moonPng += "waning-gibbous-5.png";
  } else if (_moonPhase == "Waning Gibbous-6") {
    moonPng += "waning-gibbous-6.png";
  } else if (_moonPhase == "Last Quarter") {
    moonPng += "last-quarter.png";
  } else if (_moonPhase == "Waning Crescent-1") {
    moonPng += "waning-crescent-1.png";
  } else if (_moonPhase == "Waning Crescent-2") {
    moonPng += "waning-crescent-2.png";
  } else if (_moonPhase == "Waning Crescent-3") {
    moonPng += "waning-crescent-3.png";
  } else if (_moonPhase == "Waning Crescent-4") {
    moonPng += "waning-crescent-4.png";
  } else if (_moonPhase == "Waning Crescent-5") {
    moonPng += "waning-crescent-5.png";
  } else if (_moonPhase == "Waning Crescent-6") {
    moonPng += "waning-crescent-6.png";
  } else {
    moonPng = "/icons/96/wi-moon-alt-waning-gibbous-2.png";  // default
  }
  return moonPng;
}
