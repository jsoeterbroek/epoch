#ifndef CAL_SAKA_H
#define CAL_SAKA_H

#include <array>
#include <string>
#include <astro.h>
#include <calendar.h>

// Constants
constexpr double SAKA_EPOCH = 1749994.5;  // JD of March 22, 78 CE

// Function declarations
std::array<int, 3> jd_to_saka(double jd);
std::string format_saka_date(double jd);
std::string format_saka_date_day(double jd);
std::string format_saka_date_local(double jd, bool use_hindi);
std::string format_saka_date_weekday_local(double jd, bool use_hindi);
std::string format_saka_date_month_local(double jd, bool use_hindi);
std::string format_saka_date_year_local(double jd, bool use_hindi);

#endif  // CAL_SAKA_H
