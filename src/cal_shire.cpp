#include "cal_shire.h"
#include "calendar.h"
#include <cmath>
#include <string>
#include <array>

/* 
| S.R. Year | Afteryule 1 | Gregorian Date | JD        |
| --------- | ----------- | -------------- | --------- |
| 1         | 1601-01-02  | 1601-01-02     | 2305814.5 |
| 1421      | 2021-01-02  | 2021-01-02     | 2459216.5 | 
*/
constexpr double SHIRE_EPOCH = 2305814.5;  // 1601-01-02 Gregorian = S.R. 1, Afteryule 1

// Shire months (1-based)
const char *shire_months[12] = {"Afteryule",  "Solmath", "Rethe",    "Astron",      "Thrimidge", "Forelithe",
                                "Afterlithe", "Wedmath", "Halimath", "Winterfilth", "Blotmath",  "Foreyule"};

// Shire weekdays (Sterday is 0, Sunday is 1, ..., Highday is 6)
const char *shire_weekdays[7] = {"Sterday", "Sunday", "Monday", "Trewsday", "Hevensday", "Mersday", "Highday"};

// Shire holidays (codes)
enum ShireHoliday {
  HOL_NONE = 0,
  HOL_YULE1 = 1,
  HOL_YULE2 = 2,
  HOL_1LITHE = 3,
  HOL_MIDYEARS = 4,
  HOL_OVERLITHE = 5,  // Only in leap years
  HOL_2LITHE = 6
};

const char *shire_holidays[7] = {"", "1 Yule", "2 Yule", "1 Lithe", "Midyear's Day", "Overlithe", "2 Lithe"};

// Given JD, get days since SHIRE_EPOCH
inline int days_since_shire_epoch(double jd) {
  return static_cast<int>(std::floor(jd) - std::floor(SHIRE_EPOCH));
}

std::array<int, 4> jd_to_shire(double jd) {
  int days = days_since_shire_epoch(jd);

  // Estimate year
  int approx_year = static_cast<int>(days / 366.0) + 1;
  int start_of_year =
    static_cast<int>(std::floor(SHIRE_EPOCH)) + (approx_year - 1) * 365 + ((approx_year - 1) / 4 - (approx_year - 1) / 100 + (approx_year - 1) / 400);

  // Count days into the Shire year
  int day_of_year = static_cast<int>(std::floor(jd)) - start_of_year + 1;
  int year = approx_year;

  bool leap = is_shire_leap(year);

  // Map days to holidays and months
  // Shire New Year structure:
  // 1 Yule (holiday), 30 Afteryule, 30 Solmath, ..., 30 Foreyule, 2 Yule (holiday)
  // Between Forelithe and Afterlithe: 1 Lithe (holiday), Midyear's Day (holiday), Overlithe (leap year only), 2 Lithe (holiday)

  // Holidays and their absolute day-of-year positions (1-based)
  int lithe_start = 181;                // After 6 months of 30 days (180)
  int midyears_day = leap ? 183 : 182;  // leap: Overlithe is after Midyear's Day
  int overlithe = 183;
  int two_lithe = leap ? 184 : 183;
  int last_month_start = leap ? 185 : 184;

  // 1 Yule (day 1)
  if (day_of_year == 1) {
    return {year, 0, 0, HOL_YULE1};
  }
  // 2 Yule (last day)
  if ((leap && day_of_year == 366) || (!leap && day_of_year == 365)) {
    return {year, 0, 0, HOL_YULE2};
  }

  // First 6 months
  if (day_of_year >= 2 && day_of_year <= 181) {
    int day_in_year = day_of_year - 2;
    int month = (day_in_year / 30) + 1;
    int day = (day_in_year % 30) + 1;
    return {year, month, day, HOL_NONE};
  }

  // Lithe/holiday block
  if (day_of_year == lithe_start + 1) {
    return {year, 0, 0, HOL_1LITHE};
  }
  if ((!leap && day_of_year == lithe_start + 2) || (leap && day_of_year == lithe_start + 2)) {
    return {year, 0, 0, HOL_MIDYEARS};
  }
  if (leap && day_of_year == lithe_start + 3) {
    return {year, 0, 0, HOL_OVERLITHE};
  }
  if ((!leap && day_of_year == lithe_start + 3) || (leap && day_of_year == lithe_start + 4)) {
    return {year, 0, 0, HOL_2LITHE};
  }

  // Last 6 months
  int month_offset = leap ? two_lithe : two_lithe - 1;
  if (day_of_year > month_offset && day_of_year < (leap ? 366 : 365)) {
    int day_in_year = day_of_year - (month_offset + 1);
    int month = (day_in_year / 30) + 7;
    int day = (day_in_year % 30) + 1;
    return {year, month, day, HOL_NONE};
  }

  // Should not reach here; fallback
  return {year, 0, 0, 0};
}

inline bool is_shire_leap(int year) {
  int gregorian_year = year + 1600;  // S.R. 1 = 1601
  return (gregorian_year % 4 == 0 && (gregorian_year % 100 != 0 || gregorian_year % 400 == 0));
}

// Main function:
double shire_to_jd(int year, int month, int day, int holiday_code) {
  // Start of S.R. year (S.R. 1 = 1601-01-02 Gregorian = JD 2305814.5)
  // Each Shire year starts on Jan 2 of Gregorian year (year + 1600)
  int gregorian_year = year + 1600;
  int years_since_epoch = gregorian_year - 1601;
  double jd = SHIRE_EPOCH + years_since_epoch * 365 + (years_since_epoch / 4 - years_since_epoch / 100 + years_since_epoch / 400);

  bool leap = is_shire_leap(year);

  // Holidays (month = 0)
  if (month == 0) {
    int lithe_start = 180;  // After first 6 months (6*30)
    if (holiday_code == 1) {
      return jd;  // 1 Yule (first day of the year)
    }
    if (holiday_code == 2) {
      return jd + (leap ? 365 : 364);  // 2 Yule (last day)
    }
    if (holiday_code == 3) {
      return jd + lithe_start + 1;  // 1 Lithe
    }
    if (holiday_code == 4) {
      return jd + lithe_start + 2;  // Midyear's Day
    }
    if (leap && holiday_code == 5) {
      return jd + lithe_start + 3;  // Overlithe (leap year only)
    }
    if (holiday_code == 6) {
      return jd + lithe_start + (leap ? 4 : 3);  // 2 Lithe
    }
    // Default fallback for unknown holiday: return start of year
    return jd;
  }
  // Months
  if (month >= 1 && month <= 12 && day >= 1 && day <= 30) {
    if (month <= 6) {
      return jd + (month - 1) * 30 + day;
    } else {
      int lithe_days = leap ? 4 : 3;
      return jd + 180 + lithe_days + (month - 7) * 30 + day;
    }
  }
  // Fallback (invalid month/day): return start of year
  return jd;
}

std::string shire_month_name(int month) {
  if (month >= 1 && month <= 12) {
    return shire_months[month - 1];
  }
  return "";
}

std::string shire_weekday_name(int weekday) {
  if (weekday >= 0 && weekday < 7) {
    return shire_weekdays[weekday];
  }
  return "";
}

std::string shire_holiday_name(int code) {
  if (code > 0 && code < 7) {
    return shire_holidays[code];
  }
  return "";
}

std::string format_shire_date(const std::array<int, 4> &date) {
  int year = date[0], month = date[1], day = date[2], holiday = date[3];
  if (month == 0 && holiday != HOL_NONE) {
    return std::to_string(year) + " " + shire_holiday_name(holiday);
  } else {
    // Calculate weekday
    double jd = shire_to_jd(year, month, day);
    int weekday = (static_cast<int>(std::floor(jd + 1.5)) % 7);
    return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + " (" + shire_month_name(month) + " " + std::to_string(day) + ", "
           + shire_weekday_name(weekday) + ")";
  }
}

std::string format_shire_date_year(double jd) {
  auto date = jd_to_shire(jd);
  return std::to_string(date[0]) + " S.R.";
}

std::string format_shire_date_month(double jd) {
  auto date = jd_to_shire(jd);
  if (date[1] == 0) {
    return shire_holiday_name(date[3]);
  }
  return shire_month_name(date[1]);
}

std::string format_shire_date_day(double jd) {
  auto date = jd_to_shire(jd);
  if (date[1] == 0) {
    return shire_holiday_name(date[3]);
  }
  return std::to_string(date[2]);
}

std::string format_shire_date_weekday(double jd) {
  auto date = jd_to_shire(jd);
  if (date[1] == 0) {
    return "";  // Holidays do not have weekdays
  }
  int weekday = (static_cast<int>(std::floor(jd + 1.5)) % 7);
  return shire_weekday_name(weekday);
}
