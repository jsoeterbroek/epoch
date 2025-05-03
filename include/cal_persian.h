#ifndef CAL_PERSIAN_H
#define CAL_PERSIAN_H

#include <array>
#include <string>
#include <astro.h>

// Constants
constexpr double PERSIAN_EPOCH = 1948320.5;  // March 19, 622 CE (Julian)

// Function declarations
std::string format_persian_date(double jd);

#endif // CAL_PERSIAN_H
