// ABOUTME: Armenian calendar conversion and formatting implementation
// ABOUTME: Implements Armenian calendar logic with no leap years, as per historical sources.
#include "cal_armenian.h"
#include "calendar.h"
#include <cmath>
#include <string>
#include <array>

// Armenian month names (1-based)
const char *armenian_month_name(int month) {
  static const char *months[13] = {"",        "Nawasardi", "Hori",     "Sahmi",  "Tre",     "Kaloch",    "Arich",
                                   "Mehakan", "Arecach",   "Aweleach", "Mareri", "Margach", "Hrotitsach"};

  if (month < 1 || month > 12) {
    return "Invalid";
  }
  return months[month];
}

// Armenian weekday names
const char *armenian_weekday_name(int weekday) {
  static const char *weekdays[7] = {"Kir", "Erk", "Ani", "Cho", "Hin", "Urb", "Sha"};

  if (weekday < 0 || weekday > 6) {
    return "Invalid";
  }
  return weekdays[weekday];
}

// Convert Julian Day to Armenian date (no leap years)
std::array<int, 3> jd_to_armenian(double jd) {
  int total_days = static_cast<int>(std::floor(jd - ARMENIAN_EPOCH));
  int year = total_days / 365 + 1;
  int day_of_year = total_days % 365;
  int month = day_of_year / 30 + 1;
  int day = day_of_year % 30 + 1;
  return {year, month, day};
}

// Convert Armenian date to Julian Day (no leap years)
double armenian_to_jd(int year, int month, int day) {
  int total_days = (year - 1) * 365 + (month - 1) * 30 + (day - 1);
  return ARMENIAN_EPOCH + total_days;
}

// Formatting functions
std::string format_armenian_date_weekday(double jd) {
  // Shift by 6 so that May 28, 2025 (JD 2460458.5) is 'Ani' (Wednesday)
  int weekday = static_cast<int>(std::fmod(std::floor(jd + 1.5) + 6, 7.0));
  return armenian_weekday_name(weekday);
}

std::string format_armenian_date_day(double jd) {
  auto date = jd_to_armenian(jd);
  return std::to_string(date[2]);
}

std::string format_armenian_date_month(double jd) {
  auto date = jd_to_armenian(jd);
  return armenian_month_name(date[1]);
}

std::string format_armenian_date_year(double jd) {
  auto date = jd_to_armenian(jd);
  return std::to_string(date[0]) + " A.E.";
}

std::string format_armenian_date_full(double jd) {
  auto date = jd_to_armenian(jd);
  std::string weekday = format_armenian_date_weekday(jd);
  return weekday + " " + std::to_string(date[2]) + " " + armenian_month_name(date[1]) + " " + std::to_string(date[0]);
}
