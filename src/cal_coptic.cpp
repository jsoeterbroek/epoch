#include "cal_coptic.h"
#include "astro.h"
#include <cmath>
#include <string>
#include <array>

// Coptic epoch = August 29, 284 CE (Julian) = JD 1825029.5
constexpr double COPTIC_EPOCH = 1825029.5;

// Coptic month names
const char *coptic_month_name(int month, CopticMonthVariant variant) {
  static const char *academic[13] = {"Thout",     "Paopi",   "Hathor", "Koiak", "Tobi",   "Meshir", "Paremhat",
                                     "Paremoude", "Pashons", "Paoni",  "Epip",  "Mesori", "Nasie"};

  static const char *liturgical[13] = {"Tout",      "Baba",    "Hator", "Kiahk", "Toba",  "Amshir", "Baramhat",
                                       "Baramouda", "Bashans", "Paona", "Abib",  "Misra", "Nasie"};

  if (month < 1 || month > 13) {
    return "(Invalid)";
  }
  return (variant == CopticMonthVariant::Liturgical) ? liturgical[month - 1] : academic[month - 1];
}

const char *coptic_weekday_name(int weekday, CopticWeekdayVariant variant) {
  static const char *standard[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  static const char *liturgical[7] = {"Kyriaki", "Deftera", "Triti", "Tetarti", "Pempti", "Paraskevi", "Savvato"};

  if (weekday < 0 || weekday > 6) {
    return "(Invalid)";
  }
  return (variant == CopticWeekdayVariant::Liturgical) ? liturgical[weekday] : standard[weekday];
}

// Leap year: every 4 years (like Julian)
bool is_coptic_leap(int year) {
  return year % 4 == 3;
}

// Convert Coptic → JD
double coptic_to_jd(int year, int month, int day) {
  return COPTIC_EPOCH + 365.0 * (year - 1) + std::floor((year - 1) / 4.0) + 30.0 * (month - 1) + (day - 1);
}

// Convert JD → Coptic [year, month, day]
std::array<int, 3> jd_to_coptic(double jd) {
  jd = std::floor(jd) + 0.5;

  double days = jd - COPTIC_EPOCH;
  int year = static_cast<int>(std::floor((4.0 * days + 1463) / 1461.0));
  double jd_year = coptic_to_jd(year, 1, 1);
  int day_of_year = static_cast<int>(jd - jd_year);
  int month = day_of_year / 30 + 1;
  int day = day_of_year % 30 + 1;
  return {year, month, day};
}

// Formatters
std::string format_coptic_date_weekday(double jd, CopticWeekdayVariant variant) {
  int weekday = static_cast<int>(astro::mod(std::floor(jd + 1.5), 7.0));
  return coptic_weekday_name(weekday, variant);
}

std::string format_coptic_date_day(double jd, CopticDayVariant variant) {
  auto date = jd_to_coptic(jd);
  int day = date[2];
  int month = date[1];

  if (variant == CopticDayVariant::Liturgical) {
    if (month == 1 && day == 1) {
      return "Neyrouz (Coptic New Year)";
    }
    if (month == 1 && day == 2) {
      return "St. John the Baptist";
    }
    if (month == 4 && day == 29) {
      return "Nativity (if 29 Koiak)";
    }
    if (month == 8 && day == 29) {
      return "Resurrection (if 29 Paremoude)";
    }
    // More fixed feast dates can be added here
  }
  return std::to_string(day);
}

std::string format_coptic_date_month(double jd, CopticMonthVariant variant) {
  auto date = jd_to_coptic(jd);
  return coptic_month_name(date[1], variant);
}

std::string format_coptic_date_year(double jd) {
  auto date = jd_to_coptic(jd);
  return std::to_string(date[0]) + " AM";  // Anno Martyrum
}
