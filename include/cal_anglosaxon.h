#ifndef CAL_ANGLOSAXON_H
#define CAL_ANGLOSAXON_H

#include <array>
#include <string>
#include <astro.h>

// Constants

// Function declarations
std::string format_anglosaxon_date_weekday(double jd);
std::string format_anglosaxon_date_day(double jd);
std::string format_anglosaxon_date_month(double jd);
std::string format_anglosaxon_date_year(double jd);

#endif