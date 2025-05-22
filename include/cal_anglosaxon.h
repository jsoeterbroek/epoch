#ifndef CAL_ANGLOSAXON_H
#define CAL_ANGLOSAXON_H

#include <array>
#include <string>
#include <astro.h>
#include <calendar.h>

// Constants

// Function declarations
std::array<int, 3> jd_to_anglosaxon(double jd);
bool is_anglosaxon_holiday(double jd, const std::string &name);
std::string format_anglosaxon_date(double jd);
std::string format_anglosaxon_date_weekday(double jd);
std::string format_anglosaxon_date_day(double jd);
std::string format_anglosaxon_date_month(double jd);
std::string format_anglosaxon_date_month_description(double jd);
std::string format_anglosaxon_date_year(double jd);

#endif
