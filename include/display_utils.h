/* Display helper utility declarations for esp32-weather-epd.
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

#ifndef __DISPLAY_UTILS_H__
#define __DISPLAY_UTILS_H__

#include <vector>
#include <time.h>
#include <cstdint>

uint32_t readBatteryVoltage();
uint32_t calcBatPercent(uint32_t v, uint32_t minv, uint32_t maxv);
const uint8_t *getBatBitmap24(uint32_t batPercent);
void getRefreshTimeStr(String &s, bool timeSuccess, tm *timeInfo);
const uint8_t *getWiFiBitmap16(int rssi);
//const uint8_t *getMoonBitmap24();
String getMoonPng48(String _moonPhase);
String getMoonPng96(String _moonPhase);

#endif
