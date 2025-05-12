/* converted from */
/*
       JavaScript functions for the Fourmilab Calendar Converter

                  by John Walker  --  September, MIM
              http://www.fourmilab.ch/documents/calendar/

                This program is in the public domain.
*/
#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Hebrew
//
const char *hebrew_month_name(int year, int month) {
  // Hebrew months (Nisan = 1, Tishrei = 7)
  static const char *months_common[13] = {"Nisan",    "Iyyar",  "Sivan", "Tammuz", "Av",   "Elul", "Tishrei",
                                          "Cheshvan", "Kislev", "Tevet", "Shevat", "Adar", nullptr};

  static const char *months_leap[13] = {"Nisan",    "Iyyar",  "Sivan", "Tammuz", "Av",     "Elul",   "Tishrei",
                                        "Cheshvan", "Kislev", "Tevet", "Shevat", "Adar I", "Adar II"};

  if (is_hebrew_leap(year)) {
    return months_leap[month - 1];
  } else {
    return months_common[month - 1];
  }
}

double hebrew_to_jd(int year, int month, int day) {
  double jd = HEBREW_EPOCH + hebrew_delay_1(year) + day + 1;

  if (month < 7) {
    for (int m = 7; m <= hebrew_year_months(year); m++) {
      jd += hebrew_month_days(year, m);
    }
    for (int m = 1; m < month; m++) {
      jd += hebrew_month_days(year, m);
    }
  } else {
    for (int m = 7; m < month; m++) {
      jd += hebrew_month_days(year, m);
    }
  }
  return jd;
}

std::array<int, 3> jd_to_hebrew(double jd) {
  jd = std::floor(jd) + 0.5;

  // Initial estimate of Hebrew year based on average year length (~366 days)
  int year = static_cast<int>((jd - HEBREW_EPOCH) / 366);

  // Increment until we find the correct Hebrew year
  while (jd >= hebrew_to_jd(year + 1, 7, 1)) {
    year++;
  }

  // Determine the month and day
  int month = (jd < hebrew_to_jd(year, 1, 1)) ? 7 : 1;

  while (jd > hebrew_to_jd(year, month, hebrew_month_days(year, month))) {
    month++;
  }

  int day = static_cast<int>(jd - hebrew_to_jd(year, month, 1) + 1);
  return {year, month, day};
}

bool is_hebrew_leap(int year) {
  return (((7 * year) + 1) % 19) < 7;
}

double hebrew_delay_1(int year) {
  double months = std::floor((235 * year - 234) / 19.0);
  double parts = 12084 + 13753 * months;
  double day = months * 29 + std::floor(parts / 25920.0);
  if ((static_cast<int>(3 * (day + 1)) % 7) < 3) {
    day++;
  }
  return day;
}

double hebrew_delay_2(int year) {
  return hebrew_delay_1(year + 1) - hebrew_year_days(year);
}

int hebrew_year_days(int year) {
  return static_cast<int>(hebrew_to_jd(year + 1, 7, 1) - hebrew_to_jd(year, 7, 1));
}

int hebrew_year_months(int year) {
  return is_hebrew_leap(year) ? 13 : 12;
}

int hebrew_month_days(int year, int month) {
  if (month == 2 || month == 4 || month == 6 || month == 10 || month == 13) {
    return 29;
  }
  if (month == 12 && !is_hebrew_leap(year)) {
    return 29;
  }
  if (month == 8 && ((hebrew_year_days(year) % 10) != 5)) {
    return 29;
  }
  if (month == 9 && ((hebrew_year_days(year) % 10) == 3)) {
    return 29;
  }
  return 30;
}

std::string format_hebrew_date_day(double jd) {
  auto date = jd_to_hebrew(jd);
  return std::to_string(date[2]);
}

std::string format_hebrew_date_month(double jd) {
  auto date = jd_to_hebrew(jd);
  return hebrew_month_name(date[0], date[1]);
}

std::string format_hebrew_date_year(double jd) {
  auto date = jd_to_hebrew(jd);
  return std::to_string(date[0]) + " AM";
}

std::string format_hebrew_date_weekday(double jd) {
  static const char *weekdays[] = {"Yom Rishon", "Yom Sheni", "Yom Shlishi", "Yom Revi'i", "Yom Chamishi", "Yom Shishi", "Shabbat"};
  int weekday = static_cast<int>(astro::mod(std::floor(jd + 1.5), 7.0));
  return weekdays[weekday];
}

std::string format_hebrew_full_date(double jd) {
  auto date = jd_to_hebrew(jd);
  return std::to_string(date[2]) + " " + hebrew_month_name(date[0], date[1]) + ", " + std::to_string(date[0]);
}
