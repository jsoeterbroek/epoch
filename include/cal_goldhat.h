#ifndef CAL_GOLDHAT_H
#define CAL_GOLDHAT_H

#include <string>
#include <vector>

struct GoldhatZone {
  int zone_number;
  int zone_value;
  bool intercalary;
};

enum class GoldHats {
  Berlin,
  Ezelsdorf,
  Schifferstadt,
  Avanton
};

extern const std::vector<GoldhatZone> berlin_goldhat_zones;

// Calculate sum of days for a range of zones (inclusive), optionally subtracting intercalary zones
int goldhat_sum_days(int start_zone, int end_zone, bool subtract_intercalary = true);

// Format the current Goldhat zone for a given JD (for visual pointer/calendar use)
std::string format_goldhat_zone(double jd, GoldHats goldhat = GoldHats::Berlin);

// Example: calculate days for 54 lunar months (zones 3-21 minus intercalary zones 5, 16, 17)
int goldhat_days_54_lunar_months();

#endif  // CAL_GOLDHAT_H
