#pragma once
#include <array>
#include <string>

// Shire calendar module for Epoch Calendar Project
// Conversion functions: JD <-> Shire calendar
// Epoch: S.R. 1 = 1601-01-01 Gregorian

// Convert Julian Day to Shire date [year, month, day, holiday_code]
//  - month = 0 for holidays (see holiday_code), day = 0 for holidays
std::array<int, 4> jd_to_shire(double jd);

// Convert Shire date to Julian Day
double shire_to_jd(int year, int month, int day, int holiday_code = 0);

// Get Shire month name (1-based; holidays are month=0)
std::string shire_month_name(int month);

// Get Shire weekday name (0=Sterday, 1=Sunday, ... 6=Highday)
std::string shire_weekday_name(int weekday);

// Get holiday name from code
std::string shire_holiday_name(int code);

// Format a full Shire date as a string (e.g., "1425-6-15 (Afterlithe 15, Monday)" or "1425 Yule 2")
std::string format_shire_date(const std::array<int, 4> &date);

inline bool is_shire_leap(int year);

// Format helpers
std::string format_shire_date_year(double jd);
std::string format_shire_date_month(double jd);
std::string format_shire_date_day(double jd);
std::string format_shire_date_weekday(double jd);
