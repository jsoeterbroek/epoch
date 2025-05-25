#ifndef CAL_NEGEV_H
#define CAL_NEGEV_H

#include <string>

// Format current date in the Negev rock-art Venus calendar
std::string format_nergev_venus(double jd);

// Returns 1-12: month counter (12 stones = 1 lunar year)
int format_negev_wheel(double jd);

// Returns 1-8: year counter (8 stones = 8-year Venus cycle)
int format_negev_branch(double jd);

#endif  // CAL_NEGEV_H
