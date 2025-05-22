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

// Returns [year, month, day] in Old High German calendar
std::array<int, 3> jd_to_germanic(double jd) {
  auto g = jd_to_gregorian(jd);
  int year = g[0];
  int month = g[1];
  int day = g[2];

  // Germanic months start at fixed Gregorian dates (example boundaries, adjust as needed)
  static const int month_starts[12][2] = {
    {12, 25},  // Wintar-manod (Winter month) - Dec 25
    {1, 25},   // Hornung - Jan 25
    {2, 24},   // Lenzin-manod - Feb 24
    {3, 25},   // Ostar-manod - Mar 25
    {4, 24},   // Winni-manod - Apr 24
    {5, 24},   // Brah-manod - May 24
    {6, 23},   // Hewi-manod - Jun 23
    {7, 23},   // Aran-manod - Jul 23
    {8, 22},   // Witu-manod - Aug 22
    {9, 21},   // Windume-manod - Sep 21
    {10, 21},  // Herbist-manod - Oct 21
    {11, 20}   // Hailag-manod - Nov 20
  };

  int gmonth = 0, gday = 0, gyear = year;
  for (int i = 11; i >= 0; --i) {
    int m = month_starts[i][0];
    int d = month_starts[i][1];
    if ((month > m) || (month == m && day >= d)) {
      gmonth = i + 1;
      if (month == m) {
        gday = day - d + 1;
      } else {
        int days_in_month = 31;
        if (m == 2) {
          days_in_month = 28 + ((gyear % 4 == 0 && (gyear % 100 != 0 || gyear % 400 == 0)) ? 1 : 0);
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
          days_in_month = 30;
        }
        gday = days_in_month - d + 1 + day;
      }
      break;
    }
  }
  if (gmonth == 0) {
    // Before Dec 25: still in previous year's Wintar-manod
    gmonth = 1;
    gyear -= 1;
    int days_in_dec = 31;
    gday = days_in_dec - 25 + 1 + day;
  }
  return {gyear, gmonth, gday};
}

std::string format_germanic_date(double jd) {
  auto date = jd_to_germanic(jd);
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
  auto date = jd_to_germanic(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i", date[2]);
  return std::string(buffer);
}

std::string format_germanic_date_month(double jd) {
  auto date = jd_to_germanic(jd);
  const char *month_str = germanic_month_name(date[1]);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s", month_str);
  return std::string(buffer);
}

std::string format_germanic_date_month_description(double jd) {
  auto date = jd_to_germanic(jd);
  const char *month_desc_str = germanic_month_desc(date[1]);
  char buffer[40];
  snprintf(buffer, sizeof(buffer), "%s", month_desc_str);
  return std::string(buffer);
}

std::string format_germanic_date_year(double jd) {
  auto date = jd_to_germanic(jd);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%i AD", date[0]);
  return std::string(buffer);
}
