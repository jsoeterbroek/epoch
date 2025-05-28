#ifndef CALENDAR_H
#define CALENDAR_H

#include <array>
#include <string>
#include "astro.h"
#include "_locale.h"
#include "calendar.h"

namespace calendar {

// Constants

// Function declarations
const char *calendar_name(int index);
std::array<int, 3> jd_to_iso_week(double jd);
std::array<int, 3> jd_to_iso(double jd);
int calculate_lunar_day(double jd);
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

}  // namespace calendar
#endif  // CALENDAR_H
