/*

https://mandaeansynod.org.au/mandaean-calendar.html

Tuesday 20 May 2025

Dehwa Daymaneh
Tuesday, 20 May
Annually on May 20
The day our great teacher - Yahya Yohana was born
Mandaean Calendar
Created by: nsobbi@gmail.com

*/
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "cal_mandaean.h"
#include "cal_gregorian.h"
#include <iostream>

//TEST_CASE("Mandaean calendar conversion and formatting for gregorian 20th May 2025") {
// Confirm epoch
//  double jd = gregorian_to_jd(2025, 5, 20);
//  auto date = jd_to_mandaean(jd);
//  CHECK(date[0] == 1);
//  CHECK(date[1] == 1);
//  CHECK(date[2] == 1);
//CHECK(format_mandaean_date_month(jd) == "Aria");
//  CHECK(mandanean_festival(date[1], date[2]) == "Dehwa Daymaneh");
//}

// TEST_CASE("Mandaean month, day, and weekday formatting") {
//   double jd = mandanean_to_jd(1445, 2, 10);  // Year 1445, month 2, day 10
//   CHECK(format_mandaean_date_month(jd) == "Aria");
//   CHECK(format_mandaean_date_day(jd) == "10");
//   // Weekday depends on epoch, but should be consistent with other calendars
//   // For example, let's just verify it's a valid name:
//   //std::string wd = format_mandaean_date_weekday(jd);
//   //CHECK(wd == "Monday" || wd == "Tuesday" || wd == "Wednesday" || wd == "Thursday" || wd == "Friday" || wd == "Saturday" || wd == "Sunday");
// }

TEST_CASE("Mandaean Parwanaya festival detection") {
  // The 5 epagomenal days
  double jd = mandanean_to_jd(1, 13, 3);  // 3rd Parwanaya day, year 1
  auto date = jd_to_mandaean(jd);
  CHECK(date[1] == 13);
  CHECK(date[2] == 3);
  CHECK(format_mandaean_date(date) == "1-13-3 (Parwanaya Parwanaya 3)");
  CHECK(mandanean_festival(date[1], date[2]) == "Parwanaya");
}
