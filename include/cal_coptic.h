#ifndef CAL_COPTIC_H
#define CAL_COPTIC_H

#include <array>
#include <string>

enum class CopticMonthVariant {
  Academic,   // e.g. "Pashons"
  Liturgical  // e.g. "Bashans" or "Psoou"
};
enum class CopticWeekdayVariant {
  Standard,   // English (Sunday, Monday, ...)
  Liturgical  // Coptic/Church usage (Kyriaki, etc.)
};
enum class CopticDayVariant {
  Simple,     // Just "Day 1", "Day 2", etc.
  Liturgical  // Feasts, fasts, or named observances (if known)
};

std::array<int, 3> jd_to_coptic(double jd);
double coptic_to_jd(int year, int month, int day);

std::string format_coptic_date_day(double jd, CopticDayVariant variant);
std::string format_coptic_date_month(double jd, CopticMonthVariant variant);
std::string format_coptic_date_year(double jd);
std::string format_coptic_date_weekday(double jd, CopticWeekdayVariant variant);
const char *coptic_month_name(int month, CopticMonthVariant variant);
const char *coptic_weekday_name(int weekday, CopticWeekdayVariant variant);

#endif
