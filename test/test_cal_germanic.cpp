#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_germanic.h"
#include <iostream>

/*
-------
Monday, 19 May, 2025
--------------
*/
TEST_CASE("Germanic calendar date conversion and formatting for may 19, 2025") {
  double jd = gregorian_to_jd(2025, 5, 19);
  auto date = jd_to_julian(jd);
  CHECK(date[1] == 5);
  CHECK(date[2] == 6);
  CHECK(format_germanic_date_day(jd) == "6");
  CHECK(format_germanic_date_weekday(jd) == "Manetag");
  CHECK(format_germanic_date_month(jd) == "Winni-manod");
}
