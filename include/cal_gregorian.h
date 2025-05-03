#ifndef CAL_GREGORIAN_H
#define CAL_GREGORIAN_H

#include <array>
#include <string>
#include <astro.h>


// Constants
constexpr double GREGORIAN_EPOCH = 1721425.5;

// Function declarations
bool leap_gregorian(int year);
double gregorian_to_jd(int year, int month, int day);
std::array<int, 3> jd_to_gregorian(double jd);
std::string format_gregorian_date(double jd);

#endif

