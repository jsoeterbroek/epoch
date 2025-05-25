#include "cal_goldhat.h"
#include "venus.h"
#include <string>
#include <vector>
#include <numeric>
#include <iostream>

/* 
 see file: gold_hat.md
*/

// zone, value, intercalary
const std::vector<GoldhatZone> goldhat_zones = {
  // zone, value, intercalary
  {1, 0, false},     // zone 1
  {2, 44, false},    // zone 2:
  {3, 42, false},    // zone 3:
  {4, 75, false},    // zone 4:
  {5, 38, true},     // intercalary, value 38
  {6, 90, false},    // zone 6:
  {7, 57, true},     // intercalary, value 57
  {8, 105, false},   // zone 8:
  {9, 57, false},    // zone 9:
  {10, 95, false},   // zone 10:
  {11, 60, false},   // zone 11:
  {12, 100, false},  // zone 12:
  {13, 60, false},   // zone 13:
  {14, 105, false},  // zone 14:
  {15, 90, false},   // zone 15:
  {16, 38, true},    // intercalary, value 38
  {17, 66, true},    // intercalary, value 66
  {18, 126, false},  // zone 18:
  {19, 138, false},  // zone 19:
  {20, 162, false},  // zone 20:
  {21, 235, false}   // zone 21:
};

// Calculate sum of days for a range of zones (inclusive), optionally subtracting intercalary zones
int goldhat_sum_days(int start_zone, int end_zone, bool subtract_intercalary) {
  int sum = 0;
  int intercalary_sum = 0;
  for (const auto &zone : goldhat_zones) {
    if (zone.zone_number >= start_zone && zone.zone_number <= end_zone) {
      int value = zone.zone_value;
      sum += value;
      // Only subtract zones 5, 16, 17 as intercalary for the 54 lunar month calculation
      if (subtract_intercalary && (zone.zone_number == 5 || zone.zone_number == 16 || zone.zone_number == 17)) {
        intercalary_sum += value;
      }
    }
  }
  //std::cout << "DEBUG: " << sum << " - " << intercalary_sum << std::endl;  // DEBUG: remove later
  if (subtract_intercalary) {
    sum -= intercalary_sum;
  }
  return sum;
}

// Example: calculate days for 54 lunar months (zones 3-21 minus intercalary zones 5, 16, 17)
int goldhat_days_54_lunar_months() {
  // According to Wikipedia: sum zones 3-21, subtract 5, 16, 17
  return goldhat_sum_days(3, 21, true);
}

// Format the current Goldhat zone for a given JD (for visual pointer/calendar use)
std::string format_goldhat_zone(double jd) {
  // For demonstration: map Venus day-in-cycle to a zone
  int day = venus::day_in_cycle(jd);
  int total_days = 0;
  for (const auto &zone : goldhat_zones) {
    int zone_days = zone.zone_value;
    if (day < total_days + zone_days) {
      int day_in_zone = day - total_days + 1;
      return "Zone " + std::to_string(zone.zone_number) + " (Day " + std::to_string(day_in_zone) + " of " + std::to_string(zone_days) + ")";
    }
    total_days += zone_days;
  }
  return "Zone unknown";
}

// For compatibility with previous stub
std::string format_goldhat_venus(double jd) {
  return format_goldhat_zone(jd);
}
