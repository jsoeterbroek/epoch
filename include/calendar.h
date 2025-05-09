#ifndef CALENDAR_H
#define CALENDAR_H

#include <array>
#include <string>
#include "astro.h"
#include "_locale.h"
#include "cal_babylonian.h"
#include "cal_gregorian.h"
#include "cal_julian.h"
#include "cal_rev_french.h"
#include "cal_islamic.h"
#include "cal_hebrew.h"
#include "cal_persian.h"
#include "cal_mayan.h"
#include "cal_saka.h"
#include "cal_zoroastrian.h"
#include "cal_anglosaxon.h"
#include "cal_old_high_german.h"
#include "cal_chinese_zodiac.h"
#include "cal_darian.h"


namespace calendar {

// Constants


// Function declarations
const char* calendar_name(int index);
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
