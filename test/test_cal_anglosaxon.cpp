#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_anglosaxon.h"
#include <iostream>

/*
-------
Monday, 19 May, 2025
--------------
*/
TEST_CASE("Anglosaxon calendar date conversion and formatting for may 19, 2025") {
  double jd = gregorian_to_jd(2025, 5, 19);
  auto date = jd_to_julian(jd);
  CHECK(date[1] == 5);
  CHECK(date[2] == 6);
  CHECK(format_anglosaxon_date_day(jd) == "6");
  CHECK(format_anglosaxon_date_weekday(jd) == "Monandag");
  CHECK(format_anglosaxon_date_month(jd) == "Thrimilchi");
}
