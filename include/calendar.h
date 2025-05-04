#ifndef CALENDAR_H
#define CALENDAR_H

#include <array>
#include <string>
#include <astro.h>
#include <cal_julian.h>
#include <cal_gregorian.h>
#include <cal_rev_french.h>
#include <cal_islamic.h>
#include <cal_hebrew.h>
#include <cal_persian.h>
#include <cal_mayan.h>
#include <cal_saka.h>
#include <cal_zoroastrian.h>

namespace calendar {

// Constants


// Function declarations
std::array<int, 3> jd_to_iso_week(double jd);
std::array<int, 3> jd_to_iso(double jd);
std::string format_iso_date(double jd);
std::string format_iso_week(double jd);
int iso_day_of_week(double jd);

enum Weekday {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

} // namespace calendar
#endif // CALENDAR_H
