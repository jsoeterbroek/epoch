#ifndef CAL_HEBREW_H
#define CAL_HEBREW_H

#include <array>
#include <string>
#include <astro.h>

// Constants
constexpr double HEBREW_EPOCH = -1373429.0;  // Hebrew calendar epoch: October 7, 3761 BCE (Julian)


// Function declarations
double hebrew_to_jd(int year, int month, int day);
std::array<int, 3> jd_to_hebrew(double jd);
int hebrew_month_days(int year, int month);
int hebrew_year_days(int year);
int hebrew_year_months(int year);
double hebrew_delay_1(int year);
double hebrew_delay_2(int year);
std::string format_hebrew_date(double jd);


#endif // CALENDAR_H

