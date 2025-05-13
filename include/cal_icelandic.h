#ifndef CAL_ICELANDIC_H
#define CAL_ICELANDIC_H

#include <array>
#include <string>

// JD → Icelandic calendar [year, month, day]
std::array<int, 3> jd_to_icelandic(double jd);

// Formatters
std::string format_icelandic_date_day(double jd);    // e.g. "Day 5"
std::string format_icelandic_date_month(double jd);  // e.g. "Góa"
std::string format_icelandic_date_month_description(double jd);
std::string format_icelandic_date_year(double jd);     // e.g. "Year 1054"
std::string format_icelandic_date_weekday(double jd);  // e.g. "Þórsdagur"

#endif
