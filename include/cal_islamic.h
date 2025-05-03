#ifndef CAL_ISLAMIC_H
#define CAL_ISLAMIC_H

#include <array>
#include <string>
#include <astro.h>


// Constants
constexpr double ISLAMIC_EPOCH = 1948439.5;  // July 16, 622 (Julian)


// Function declarations
std::string format_islamic_date(double jd);

#endif // CAL_ISLAMIC_H

