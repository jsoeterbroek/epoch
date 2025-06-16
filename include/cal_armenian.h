#ifndef CAL_ARMENIAN_H
#define CAL_ARMENIAN_H

#include <string>
#include <array>

// Armenian calendar implementation

// Armenian epoch: July 11, 552 CE (Julian) = July 13, 552 (Gregorian)
constexpr double ARMENIAN_EPOCH = 1922867.5;  // Confirmed epoch

// Armenian calendar functions
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
