
#ifndef CAL_ICELANDIC_H
#define CAL_ICELANDIC_H

#include <string>
#include <array>

// Returns [year, month (1–13), day] for a given Julian Day Number
std::array<int, 3> jd_to_icelandic(double jd);

// Returns the Icelandic weekday name (e.g. "Laugardagur")
std::string format_icelandic_date_weekday(double jd);

// Returns "Day N" where N is the day of the Icelandic month
std::string format_icelandic_date_day(double jd);

// Returns the Icelandic month name (e.g. "Harpa")
std::string format_icelandic_date_month(double jd);

// Returns a poetic/historical description of the current Icelandic month
std::string format_icelandic_date_month_description(double jd);

// Optional internal helper to get month index (0–12) based on JD
int get_icelandic_month_index(double jd);

#endif
