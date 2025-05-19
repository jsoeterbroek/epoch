#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Old High German (Julian)
//
const char *germanic_weekday_name(int day) {
  static const char *names[] = {"Manetag", "Ziestag", "Wuotanestag", "Donarestag", "Frijatag", "Sambaztag", "Sunnuntag"};
  return names[(day + 6) % 7];  // Wrap 1 (Mon) to 7 (Sun) → 0–6
}

const char *germanic_month_name(int month) {
  static const char *names[] = {"Wintar-manod", "Hornung",    "Lenzin-manod", "Ostar-manod",   "Winni-manod",   "Brah-manod",
                                "Hewi-manod",   "Aran-manod", "Witu-manod",   "Windume-manod", "Herbist-manod", "Hailag-manod"};
  return names[month - 1];
}

const char *germanic_month_desc(int month) {
  static const char *desc[] = {"",
                               "",
                               "Spring Month",
                               "Easter Month",
                               "Pasture Month",
                               "Fallow Month",
                               "Hay Month",
                               "Harvest month",
                               "Wood Month",
                               "Vintage Month",
                               "Autumn Month",
                               "Holy Month"};
  return desc[month - 1];
}

int germanic_jd_to_weekday(double jd) {
  return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

std::string format_germanic_date(double jd) {
  auto date = jd_to_julian(jd);
  int month = date[1];
  const char *month_str = germanic_month_name(month);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i %s %i", date[2], month_str, date[0]);
  return std::string(buffer);
}

std::string format_germanic_date_weekday(double jd) {
  int weekday = calendar::iso_day_of_week(jd);  // ISO: Mon=1, Sun=7
  const char *weekday_name = germanic_weekday_name(germanic_jd_to_weekday(jd));
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", weekday_name);
  return std::string(buffer);
}

std::string format_germanic_date_day(double jd) {
  auto date = jd_to_julian(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i", date[2]);
  return std::string(buffer);
}

std::string format_germanic_date_month(double jd) {
  auto date = jd_to_julian(jd);
  const char *month_str = germanic_month_name(date[1]);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", month_str);
  return std::string(buffer);
}

std::string format_germanic_date_month_description(double jd) {
  auto date = jd_to_julian(jd);
  const char *month_desc_str = germanic_month_desc(date[1]);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s", month_desc_str);
  return std::string(buffer);
}

std::string format_germanic_date_year(double jd) {
  auto date = jd_to_julian(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i AD", date[0]);
  return std::string(buffer);
}
