#ifndef CAL_ISLAMIC_H
#define CAL_ISLAMIC_H

#include <array>
#include <string>
#include <astro.h>

// Constants
constexpr double ISLAMIC_EPOCH = 1948439.5;  // July 16, 622 (Julian)

// Function declarations
std::array<int, 3> jd_to_islamic(double jd);
double islamic_to_jd(int year, int month, int day);
int islamic_is_leap_year(int year);
std::string format_islamic_date(double jd);
std::string format_islamic_date_local(double jd, bool use_arabic);
std::string format_islamic_date_weekday_local(double jd, bool use_arabic);
std::string format_islamic_date_day_local(double jd, bool use_arabic);
std::string format_islamic_date_month_local(double jd, bool use_arabic);
std::string format_islamic_date_year_local(double jd, bool use_arabic);

#endif  // CAL_ISLAMIC_H
