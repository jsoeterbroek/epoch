#ifndef CAL_MAYAN_H
#define CAL_MAYAN_H

#include <array>
#include <string>
#include <astro.h>

// Constants
constexpr double MAYAN_EPOCH = 584283.5;  // August 11, 3114 BCE (Gregorian)

// Function declarations
std::string format_mayan_date_long(double jd);
std::string format_mayan_date_day(double jd);
std::string format_mayan_date_month(double jd);

#endif  // CAL_MAYAN_H
