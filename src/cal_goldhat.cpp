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
const std::vector<GoldhatZone> berlin_goldhat_zones = {
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

// Additional goldhat zone data for different artifacts
const std::vector<GoldhatZone> ezelsdorf_goldhat_zones = {
  // FIXME: Based on Ezelsdorf gold hat - adjust values as needed
  {1, 0, false},    // zone 1
  {2, 40, false},   // zone 2
  {3, 38, false},   // zone 3
  {4, 70, false},   // zone 4
  {5, 35, true},    // intercalary
  {6, 85, false},   // zone 6
  {7, 55, true},    // intercalary
  {8, 100, false},  // zone 8
  // Add more zones as needed for Ezelsdorf
};

const std::vector<GoldhatZone> schifferstadt_goldhat_zones = {
  // FIXME: Based on Schifferstadt gold hat - adjust values as needed
  {1, 0, false},    // zone 1
  {2, 42, false},   // zone 2
  {3, 40, false},   // zone 3
  {4, 72, false},   // zone 4
  {5, 36, true},    // intercalary
  {6, 88, false},   // zone 6
  {7, 56, true},    // intercalary
  {8, 102, false},  // zone 8
  // Add more zones as needed for Schifferstadt
};

const std::vector<GoldhatZone> avanton_goldhat_zones = {
  // FIXME: Based on Avanton gold hat - adjust values as needed
  {1, 0, false},    // zone 1
  {2, 41, false},   // zone 2
  {3, 39, false},   // zone 3
  {4, 71, false},   // zone 4
  {5, 37, true},    // intercalary
  {6, 87, false},   // zone 6
  {7, 54, true},    // intercalary
  {8, 101, false},  // zone 8
  // Add more zones as needed for Avanton
};

// Helper function to get zone data for specific goldhat
const std::vector<GoldhatZone> &get_goldhat_zones(GoldHats goldhat) {
  switch (goldhat) {
    case GoldHats::Berlin:        return berlin_goldhat_zones;
    case GoldHats::Ezelsdorf:     return ezelsdorf_goldhat_zones;
    case GoldHats::Schifferstadt: return schifferstadt_goldhat_zones;
    case GoldHats::Avanton:       return avanton_goldhat_zones;
    default:                      return berlin_goldhat_zones;
  }
}

// Calculate sum of days for a range of zones (inclusive), optionally subtracting intercalary zones
int goldhat_sum_days(int start_zone, int end_zone, bool subtract_intercalary) {
  int sum = 0;
  int intercalary_sum = 0;
  for (const auto &zone : berlin_goldhat_zones) {
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
std::string format_goldhat_zone(double jd, GoldHats goldhat) {
  // Map Venus day-in-cycle to a zone
  int day = venus::day_in_cycle(jd);
  const auto &zones = get_goldhat_zones(goldhat);

  int total_days = 0;
  for (const auto &zone : zones) {
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
  return format_goldhat_zone(jd, GoldHats::Berlin);
}
