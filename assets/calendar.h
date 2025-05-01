#ifndef CALENDAR_H
#define CALENDAR_H

#include <array>

namespace calendar {

// Constants
constexpr double J0000 = 1721424.5;
constexpr double J1970 = 2440587.5;
constexpr double JMJD  = 2400000.5;
constexpr double J1900 = 2415020.5;
constexpr double J1904 = 2416480.5;
constexpr double JULIAN_EPOCH = 1721423.5;
constexpr double GREGORIAN_EPOCH = 1721425.5;

// Function declarations
bool leap_gregorian(int year);
bool leap_julian(int year);
double gregorian_to_jd(int year, int month, int day);
std::array<int, 3> jd_to_gregorian(double jd);
double julian_to_jd(int year, int month, int day);
std::array<int, 3> jd_to_julian(double jd);

} // namespace calendar
  //
constexpr double ISLAMIC_EPOCH = 1948439.5;  // July 16, 622 (Julian)
constexpr double HEBREW_EPOCH = -1373429.0;  // Hebrew calendar epoch: October 7, 3761 BCE (Julian)
constexpr double PERSIAN_EPOCH = 1948320.5;  // March 19, 622 CE (Julian)
constexpr double FRENCH_REV_EPOCH = 2375839.5;  // 22 September 1792 (Gregorian)

 
enum Weekday {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

#endif // CALENDAR_H

