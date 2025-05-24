#include "cal_goldhat.h"
#include "venus.h"
#include <string>
#include <vector>
#include <numeric>

/* 
 https://en.wikipedia.org/wiki/Berlin_Gold_Hat
 https://www.quantenbit.physik.uni-mainz.de/files/2020/03/Goldhut-TSchmidtKaler-2012.pdf
*/

// Data for Berlin Gold Hat zones (example, based on Wikipedia and Schmidt-Kaler 2012)
// zone_number, symbol_count, rings_per_symbol, intercalary, intercalary_value
const std::vector<GoldhatZone> goldhat_zones = {
  // zone, symbols, rings, intercalary, intercalary_value
  {1, 19, 5, false, 0},  {2, 20, 5, false, 0},  {3, 20, 5, false, 0},  {4, 20, 5, false, 0},  {5, 38, 1, true, 38},  // intercalary
  {6, 20, 5, false, 0},  {7, 20, 5, true, 0},                                                                        // intercalary (value by sum)
  {8, 20, 5, false, 0},  {9, 20, 5, false, 0},  {10, 20, 5, false, 0}, {11, 20, 5, false, 0}, {12, 20, 5, false, 0},
  {13, 20, 5, false, 0}, {14, 20, 5, false, 0}, {15, 20, 5, false, 0}, {16, 20, 5, true, 0},  // intercalary (value by sum)
  {17, 20, 5, true, 0},                                                                       // intercalary (value by sum)
  {18, 20, 5, false, 0}, {19, 20, 5, false, 0}, {20, 20, 5, false, 0}, {21, 20, 5, false, 0}
  // ... fill in all zones as needed ...
};

// Calculate sum of days for a range of zones (inclusive), optionally subtracting intercalary zones
int goldhat_sum_days(int start_zone, int end_zone, bool subtract_intercalary) {
  int sum = 0;
  int intercalary_sum = 0;
  for (const auto &zone : goldhat_zones) {
    if (zone.zone_number >= start_zone && zone.zone_number <= end_zone) {
      int value = zone.symbol_count * zone.rings_per_symbol;
      sum += value;
      if (subtract_intercalary && zone.intercalary) {
        // Use intercalary_value if set, else use value
        intercalary_sum += (zone.intercalary_value > 0) ? zone.intercalary_value : value;
      }
    }
  }
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
    int zone_days = zone.symbol_count * zone.rings_per_symbol;
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
