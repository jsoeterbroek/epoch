/* converted from */
/*
       JavaScript functions for the Fourmilab Calendar Converter

                  by John Walker  --  September, MIM
              http://www.fourmilab.ch/documents/calendar/

                This program is in the public domain.
*/
#include "calendar.h"
#include "cal_gregorian.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>
// icon header files
#include "display_utils.h"
#include <cstdint>

namespace calendar {

// helper functions
int jd_to_weekday(double jd) {
  return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

const char *calendar_name(int index) {
  static const char *calendar_names[] = {
    "Babylonian",             //  0
    "Gregorian",              //  1
    "Julian",                 //  2
    "Hebrew",                 //  3
    "Islamic",                //  4
    "Old Egyptian",           //  5
    "Coptic",                 //  6
    "Mayan",                  //  7
    "Persian",                //  8
    "French Republican",      //  9
    "Indian National",        // 10
    "Icelandic",              // 11
    "Anglo-Saxon",            // 12
    "Germanic",               // 13
    "Armenian",               // 14
    "Georgian",               // 15
    "Mandaean",               // 16
    "Chinese Zodiac",         // 17
    "Buddhist (Thai solar)",  // 18
    "Mongolian",              // 19
    "Ethiopian",              // 20
    "Zoroastrian Fasli",      // 21
    "Hindu",                  // 22
    "Mars"                    // 23
  };
  return calendar_names[index % 24];
};

const char *day_of_week_name(int weekday) {
  static const char *names[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  return names[weekday % 7];
}

int iso_day_of_week(double jd) {
  int dow = static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
  return dow == 0 ? 7 : dow;  // Convert Sunday (0) to 7
}

double iso_to_jd(int year, int week, int day) {
  double jan4_jd = gregorian_to_jd(year, 1, 4);
  int jan4_dow = calendar::iso_day_of_week(jan4_jd);  // Monday = 1 ... Sunday = 7
  double week1_start = jan4_jd - (jan4_dow - 1);      // JD of Monday in ISO week 1

  return week1_start + (week - 1) * 7 + (day - 1);
}

std::array<int, 3> jd_to_iso(double jd) {
  int year = jd_to_gregorian(jd - 3)[0];

  // If this JD is in the next ISO year
  if (jd >= gregorian_to_jd(year + 1, 1, 4) - calendar::iso_day_of_week(gregorian_to_jd(year + 1, 1, 4)) + 1) {
    year++;
  }

  double jan4_jd = gregorian_to_jd(year, 1, 4);
  int jan4_dow = calendar::iso_day_of_week(jan4_jd);  // Monday=1..Sunday=7
  double week1_start = jan4_jd - (jan4_dow - 1);

  int week = static_cast<int>(std::floor((jd - week1_start) / 7.0)) + 1;

  int day = calendar::iso_day_of_week(jd);  // Monday=1..Sunday=7

  return {year, week, day};
}

std::array<int, 3> jd_to_iso_week(double jd) {
  // Start by converting JD to Gregorian
  auto gdate = jd_to_gregorian(jd);
  int year = gdate[0];

  // Find JD of the Thursday of the current ISO week
  int weekday = iso_day_of_week(jd);
  double thursday_jd = jd + (4 - weekday);

  // Get the ISO week year (may differ from Gregorian year)
  auto thursday_date = jd_to_gregorian(thursday_jd);
  int week_year = thursday_date[0];

  // JD of January 4 of the ISO week year (guaranteed to be in week 1)
  double jan4 = gregorian_to_jd(week_year, 1, 4);
  int jan4_weekday = iso_day_of_week(jan4);

  // JD of the Monday of week 1
  double week1_start = jan4 - (jan4_weekday - 1);

  // Compute ISO week number
  int week = static_cast<int>(std::floor((jd - week1_start) / 7.0) + 1);

  return {week_year, week, weekday};
}

const char *iso_weekday_name(int weekday) {
  static const char *names[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  if (weekday < 1 || weekday > 7) {
    return "Invalid";
  }
  return names[weekday - 1];
}

std::string format_iso_week(double jd) {
  auto date = calendar::jd_to_iso_week(jd);
  return "ISO week: " + std::to_string(date[2]) + "/" + std::to_string(date[1]) + "/" + std::to_string(date[0]);
}

std::string format_iso_date(double jd) {
  auto iso = jd_to_iso(jd);
  int year = iso[0];
  int week = iso[1];
  int weekday = iso[2];
  const char *name = iso_weekday_name(weekday);

  char buffer[40];
  snprintf(buffer, sizeof(buffer), "ISO: %d-W%02d-%d (%s)", year, week, weekday, name);
  return std::string(buffer);
}

int calculate_lunar_day(double jd) {
  constexpr double SYNODIC_MONTH = 29.53059;
  constexpr double NEW_MOON_ANCHOR = 2451550.1;  // 2000-01-06 new moon

  // Days since anchor new moon
  double days_since = jd - NEW_MOON_ANCHOR;

  // Moon age in days
  double moon_age = std::fmod(days_since, SYNODIC_MONTH);
  if (moon_age < 0) {
    moon_age += SYNODIC_MONTH;
  }

  // Lunar day is moon age rounded down + 1
  return static_cast<int>(std::floor(moon_age)) + 1;
}

// Compute the phase angle of the moon (0=new, 180=full)
double moon_phase_angle(double jd) {
  // Use Fourmilab's mean elongation approximation
  constexpr double SYNODIC_MONTH = 29.53059;
  constexpr double NEW_MOON_ANCHOR = 2451550.1;  // 2000-01-06 new moon
  double days_since = jd - NEW_MOON_ANCHOR;
  double phase = std::fmod(days_since, SYNODIC_MONTH);
  if (phase < 0) {
    phase += SYNODIC_MONTH;
  }
  return (phase / SYNODIC_MONTH) * 360.0;
}

// NOTE: This is a stub for using the USNO API for moon phase names.
// In practice, you would need to perform an HTTP GET request to the USNO API
// (https://aa.usno.navy.mil/data/api) and parse the JSON response.
// This requires an HTTP client and a JSON parser, which are not shown here.
// The functions below show the intended structure.

#include <string>

// Example stub for querying the USNO API (synchronous, blocking, for illustration only)
std::string query_usno_moon_phase(const std::string &date_iso) {
  // Example API endpoint:
  // https://aa.usno.navy.mil/api/moon/phases/date?date=2025-05-21
  // You would use an HTTP client to GET this URL and parse the JSON response.
  // For now, return an empty string or a placeholder.
  // In production, use a library like ArduinoHttpClient or similar for ESP32.
  return "";  // Not implemented: network code required
}

// Use USNO API for simple phase name (stub)
std::string moon_phase_name_simple(double jd) {
  // Convert JD to Gregorian date (YYYY-MM-DD)
  auto g = jd_to_gregorian(jd);
  char date_iso[16];
  snprintf(date_iso, sizeof(date_iso), "%04d-%02d-%02d", g[0], g[1], g[2]);
  std::string phase = query_usno_moon_phase(date_iso);
  if (!phase.empty()) {
    return phase;
  }
  // Fallback to local calculation if API not available
  double angle = moon_phase_angle(jd);
  if (angle < 22.5 || angle >= 337.5) {
    return "New Moon";
  }
  if (angle < 67.5) {
    return "Waxing Crescent";
  }
  if (angle < 112.5) {
    return "First Quarter";
  }
  if (angle < 157.5) {
    return "Waxing Gibbous";
  }
  if (angle < 202.5) {
    return "Full Moon";
  }
  if (angle < 247.5) {
    return "Waning Gibbous";
  }
  if (angle < 292.5) {
    return "Last Quarter";
  }
  return "Waning Crescent";
}

// Use USNO API for detailed phase name (stub)
std::string moon_phase_name_detailed(double jd) {
  // Convert JD to Gregorian date (YYYY-MM-DD)
  auto g = jd_to_gregorian(jd);
  char date_iso[16];
  snprintf(date_iso, sizeof(date_iso), "%04d-%02d-%02d", g[0], g[1], g[2]);
  std::string phase = query_usno_moon_phase(date_iso);
  if (!phase.empty()) {
    return phase;
  }
  // Fallback to local calculation if API not available
  double angle = moon_phase_angle(jd);
  if (angle < 7.5 || angle >= 352.5) {
    return "New Moon";
  }
  if (angle < 22.5) {
    return "Waxing Crescent-1";
  }
  if (angle < 37.5) {
    return "Waxing Crescent-2";
  }
  if (angle < 52.5) {
    return "Waxing Crescent-3";
  }
  if (angle < 67.5) {
    return "Waxing Crescent-4";
  }
  if (angle < 82.5) {
    return "Waxing Crescent-5";
  }
  if (angle < 97.5) {
    return "Waxing Crescent-6";
  }
  if (angle < 112.5) {
    return "First Quarter";
  }
  if (angle < 127.5) {
    return "Waxing Gibbous-1";
  }
  if (angle < 142.5) {
    return "Waxing Gibbous-2";
  }
  if (angle < 157.5) {
    return "Waxing Gibbous-3";
  }
  if (angle < 172.5) {
    return "Waxing Gibbous-4";
  }
  if (angle < 187.5) {
    return "Waxing Gibbous-5";
  }
  if (angle < 202.5) {
    return "Waxing Gibbous-6";
  }
  if (angle < 217.5) {
    return "Full Moon";
  }
  if (angle < 232.5) {
    return "Waning Gibbous-1";
  }
  if (angle < 247.5) {
    return "Waning Gibbous-2";
  }
  if (angle < 262.5) {
    return "Waning Gibbous-3";
  }
  if (angle < 277.5) {
    return "Waning Gibbous-4";
  }
  if (angle < 292.5) {
    return "Waning Gibbous-5";
  }
  if (angle < 307.5) {
    return "Last Quarter";
  }
  if (angle < 322.5) {
    return "Waning Crescent-1";
  }
  if (angle < 337.5) {
    return "Waning Crescent-2";
  }
  if (angle < 352.5) {
    return "Waning Crescent";
  }
  return "New Moon";
}

// Format a string with phase name
std::string format_moon_phase(double jd) {
  return moon_phase_name_simple(jd);
}

std::string format_moon_phase_detailed(double jd) {
  return moon_phase_name_detailed(jd);
}

// Optionally, adjust JD for local time using TIMEZONE, LAT, LON
// Example usage:
// double local_jd = jd + (timezone_offset_hours / 24.0);
// std::string phase = format_moon_phase(local_jd);
}  // namespace calendar
