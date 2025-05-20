#ifndef CAL_HINDU_H
#define CAL_HINDU_H

#include <array>
#include <string>
#include <astro.h>

// Constants

// Function declarations
std::array<int, 3> jd_to_hindu_lunar(double jd);             // [year, month_index, tithi]
bool is_hindu_festival(double jd, const std::string &name);  // e.g. "Apara Ekadashi"
std::string format_hindu_date_year(double jd);
std::string format_hindu_date_month(double jd);
std::string format_hindu_date_day(double jd);
std::string format_hindu_date_weekday(double jd);

#endif
