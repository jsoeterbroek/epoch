#include "cal_ethiopian.h"
#include "astro.h"
#include "cal_gregorian.h"
#include <cmath>
#include <string>
#include <array>

// Ethiopian epoch: August 29, 8 CE (Julian) = JD 1724220.5
constexpr double ETHIOPIAN_EPOCH = 1724220.5;

static const char *ETHIOPIAN_MONTHS[13] = {"Mäskäräm", "Teqemt", "Hedar", "Tahsas", "Tir",    "Yäkatit", "Mägabit",
                                           "Miyazya",  "Genbot", "Säne",  "Hamle",  "Nähase", "Paguemen"};

static const char *WEEKDAYS[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Leap year every 4 years (same as Julian)
bool is_ethiopian_leap(int year) {
  return year % 4 == 3;
}

// Convert Ethiopian → JD
double ethiopian_to_jd(int year, int month, int day) {
  return ETHIOPIAN_EPOCH + 365.0 * (year - 1) + std::floor((year - 1) / 4.0) + 30.0 * (month - 1) + (day - 1);
}

// Convert JD → [year, month, day]
std::array<int, 3> jd_to_ethiopian(double jd) {
  jd = std::floor(jd) + 0.5;

  double days = jd - ETHIOPIAN_EPOCH;
  int year = static_cast<int>(std::floor((4.0 * days + 1463) / 1461.0));
  double jd_year = ethiopian_to_jd(year, 1, 1);
  int day_of_year = static_cast<int>(jd - jd_year);

  int month = day_of_year / 30 + 1;
  int day = day_of_year % 30 + 1;

  return {year, month, day};
}

// Formatters
std::string format_ethiopian_date_day(double jd) {
  auto date = jd_to_ethiopian(jd);
  return "Day " + std::to_string(date[2]);
}

std::string format_ethiopian_date_month(double jd) {
  auto date = jd_to_ethiopian(jd);
  return ETHIOPIAN_MONTHS[date[1] - 1];
}

std::string format_ethiopian_date_year(double jd) {
  auto date = jd_to_ethiopian(jd);
  return "Year " + std::to_string(date[0]);
}

std::string format_ethiopian_date_weekday(double jd) {
  int weekday = static_cast<int>(astro::mod(std::floor(jd + 1.5), 7.0));
  return WEEKDAYS[weekday];
}
