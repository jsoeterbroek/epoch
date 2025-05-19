#include "cal_buddhist.h"
#include <cmath>
#include <string>
#include "cal_gregorian.h"  // You should already have this

const char *buddhist_months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// Buddhist Era = Gregorian year + 543

std::array<int, 3> jd_to_buddhist(double jd) {
  // Use your existing Gregorian function
  auto gdate = jd_to_gregorian(jd);
  int year = gdate[0] + 543;
  int month = gdate[1];
  int day = gdate[2];
  return {year, month, day};
}

double buddhist_to_jd(int year, int month, int day) {
  // Convert Buddhist Era year to Gregorian, then to JD
  int g_year = year - 543;
  return gregorian_to_jd(g_year, month, day);
}

std::string buddhist_month_name(int month) {
  if (month >= 1 && month <= 12) {
    return buddhist_months[month - 1];
  }
  return "";
}

const char *gregorian_weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

inline int jwday(double jd) {
  return static_cast<int>(std::floor(jd + 1.5)) % 7;
}

std::string format_buddhist_date_day(double jd) {
  auto date = jd_to_buddhist(jd);
  return std::to_string(date[2]);
}

std::string format_buddhist_date_weekday(double jd) {
  return gregorian_weekdays[jwday(jd)];
}

std::string format_buddhist_date(const std::array<int, 3> &date) {
  int year = date[0], month = date[1], day = date[2];
  std::string s = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + " (";
  s += buddhist_month_name(month) + ")";
  return s;
}

std::string format_buddhist_date_month(double jd) {
  auto date = jd_to_buddhist(jd);
  return buddhist_month_name(date[1]);
}

std::string format_buddhist_date_year(double jd) {
  auto date = jd_to_buddhist(jd);
  return std::to_string(date[0]) + " BE";
}
