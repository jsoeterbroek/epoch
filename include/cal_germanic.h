#ifndef CAL_GERMANIC_H
#define CAL_GERMANIC_H

#include <array>
#include <string>
#include <astro.h>

// Constants

// Function declarations
std::string format_germanic_date(double jd);
std::string format_germanic_date_weekday(double jd);
std::string format_germanic_date_day(double jd);
std::string format_germanic_date_month(double jd);
std::string format_germanic_date_month_description(double jd);
std::string format_germanic_date_year(double jd);

#endif
