#ifndef CAL_JULIAN_H
#define CAL_JULIAN_H

#include <array>
#include <string>
#include <astro.h>


// Constants
constexpr double J0000 = 1721424.5;

constexpr double J1970 = 2440587.5;
constexpr double JMJD  = 2400000.5;
constexpr double J1900 = 2415020.5;
constexpr double J1904 = 2416480.5;
constexpr double JULIAN_EPOCH = 1721423.5;



// Function declarations
bool leap_julian(int year);
double julian_to_jd(int year, int month, int day);
std::array<int, 3> jd_to_julian(double jd);
std::string format_julian_date(double jd);
std::string format_julian_date_weekday(double jd);

#endif

