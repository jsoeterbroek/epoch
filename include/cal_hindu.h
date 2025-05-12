#ifndef CAL_HINDU_H
#define CAL_HINDU_H

#include <array>
#include <string>
#include <astro.h>

// Constants

// Function declarations
std::array<int, 3> jd_to_hindu_lunar(double jd);   // [year, month_index, tithi]
std::string format_hindu_date_year(double jd);     // e.g. "Vikrama Samvat 2082"
std::string format_hindu_date_month(double jd);    // e.g. "Vaishakha, Shukla Paksha"
std::string format_hindu_date_day(double jd);      // e.g. "Tithi 3 (Tritiya)"
std::string format_hindu_date_weekday(double jd);  // e.g. "Guru-vāra"

#endif
