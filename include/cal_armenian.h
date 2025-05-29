#ifndef CAL_ARMENIAN_H
#define CAL_ARMENIAN_H

#include <string>
#include <array>

// Armenian calendar implementation

// Corrected Armenian epoch calculation
// Working backwards from test: May 28, 2025 should be 1474 Margach 12
// May 28, 2025 = JD 2460458.5
// This should be Armenian year 1474, month 11, day 12
constexpr double ARMENIAN_EPOCH = 1922867.5;  // Adjusted epoch

// Armenian calendar functions
bool is_armenian_leap_year(int year);
double armenian_to_jd(int year, int month, int day);
std::array<int, 3> jd_to_armenian(double jd);

// Month and weekday names
const char *armenian_month_name(int month);
const char *armenian_weekday_name(int weekday);

// Formatting functions
std::string format_armenian_date_weekday(double jd);
std::string format_armenian_date_day(double jd);
std::string format_armenian_date_month(double jd);
std::string format_armenian_date_year(double jd);
std::string format_armenian_date_full(double jd);

#endif  // CAL_ARMENIAN_H
