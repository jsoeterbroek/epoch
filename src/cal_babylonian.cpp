// cal_babylonian.cpp
#include "cal_babylonian.h"
#include <cmath>
#include <cstdio>

//
// Babylonian (Seleucid area)
//
//
// Type: Lunisolar
//
// * Months: 12 lunar months (~29.5 days each)
// * Intercalation: 7 intercalary months added over a 19-year cycle (Metonic cycle)
// * Month Start: First visible crescent moon after sunset
// * Year Start: Around the vernal equinox (Nisannu 1)

// Babylonian month names (13 months max + 1 for Ululu II)
static const char *const BABYLONIAN_MONTHS[14] = {"Nisannu",   "Ayyaru",  "Simanu", "Du'uzu",   "Abu",    "Ululu",     "Tashritu",
                                                  "Aratsamna", "Kislimu", "Ṭebetu", "Shabaatu", "Addaru", "Addaru II", "Ululu II"};

// Weekday names in a standard 7-day cycle
static const char *const BABYLONIAN_WEEKDAYS[7] = {"Umu 1", "Umu 2", "Umu 3", "Umu 4", "Umu 5", "Umu 6", "Umu 7"};

// Julian Day of Babylonian Era start (Seleucid Era = 1 October 312 BCE = JD 1671739.5)
static constexpr double BABYLONIAN_EPOCH = 1671739.5;
static constexpr double SYNODIC_MONTH = 29.53059;

// Returns the Babylonian year in 19-year cycle (1 to 19)
int metonic_cycle_year(int year) {
  return (year - 1) % 19 + 1;
}

// Returns true if given year in Seleucid Era has an intercalary month
bool has_intercalary_month(int year) {
  switch (metonic_cycle_year(year)) {
    case 3:
    case 6:
    case 8:
    case 11:
    case 14:
    case 17:
    case 19: return true;
    default: return false;
  }
}

// Special case: year 17 uses Ululu II instead of Addaru II
bool uses_ululu_ii(int year) {
  return metonic_cycle_year(year) == 17;
}

std::array<int, 3> jd_to_babylonian(double jd) {
  double days = std::floor(jd + 0.5) - BABYLONIAN_EPOCH;
  int year = static_cast<int>(days / (354.367 + 11.0 / 19.0 * SYNODIC_MONTH));  // approx year length

  // refine year estimate
  double year_start_jd = BABYLONIAN_EPOCH + year * 354.367 + std::floor((year * 11.0) / 19.0);
  while (jd >= year_start_jd + (has_intercalary_month(year + 1) ? 384 : 354)) {
    ++year;
    year_start_jd = BABYLONIAN_EPOCH + year * 354.367 + std::floor((year * 11.0) / 19.0);
  }

  double day_of_year = jd - year_start_jd;
  int month = 0;
  double month_start = 0;

  while (true) {
    double next_month_start = month_start + SYNODIC_MONTH;
    if (day_of_year < next_month_start || month >= 13) {
      break;
    }
    month_start = next_month_start;
    ++month;
  }

  int day = static_cast<int>(day_of_year - month_start) + 1;
  int actual_month = month;

  // Handle intercalary logic
  if (has_intercalary_month(year)) {
    if (uses_ululu_ii(year) && actual_month == 5) {
      actual_month = 13;  // Ululu II
    } else if (!uses_ululu_ii(year) && actual_month == 12) {
      actual_month = 12;  // Addaru II
    } else if (actual_month > 12) {
      actual_month = 13;  // shift for Addaru II
    }
  } else if (actual_month > 11) {
    actual_month = 12;
  }
  return {year, actual_month + 1, day};  // months are 1-based
}

std::string format_babylonian_date(double jd) {
  auto date = jd_to_babylonian(jd);
  int month = date[1];
  int day = date[2];
  const char *month_name = BABYLONIAN_MONTHS[month - 1];
  char buffer[60];
  snprintf(buffer, sizeof(buffer), "%s %d", month_name, day);
  return std::string(buffer);
}

std::string format_babylonian_date_weekday(double jd) {
  int weekday = static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
  if (weekday < 0) {
    weekday += 7;
  }
  return BABYLONIAN_WEEKDAYS[weekday];
}

std::string format_babylonian_date_year(double jd) {
  auto date = jd_to_babylonian(jd);
  int year = date[0];
  char buffer[50];
  snprintf(buffer, sizeof(buffer), "%d SE", year);
  return std::string(buffer);
}
