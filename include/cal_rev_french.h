#ifndef CAL_REV_FRENCH_H
#define CAL_REV_FRENCH_H

#include <array>
#include <string>
#include <astro.h>

// Constants
constexpr double FRENCH_REV_EPOCH = 2375839.5;  // 22 September 1792 (Gregorian)

// Function declarations
std::string format_french_date_weekday(double jd);
std::string format_french_date_day(double jd);
std::string format_french_date_month(double jd);
std::string format_french_date_month_description(double jd);
std::string format_french_date_year(double jd);

#endif
