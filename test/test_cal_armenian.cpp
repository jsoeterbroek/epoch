#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_armenian.h"
#include "cal_gregorian.h"
#include <iostream>

/*
https://planetcalc.com/8491/
---------------------------

Wednesday 28 May 2025

Year: 1474
Month: 11
Day: 12
Month name: Margach
Day name: Ani
*/

TEST_CASE("Armenian calendar date conversion for May 28, 2025") {
  double jd = gregorian_to_jd(2025, 5, 28);
  auto date = jd_to_armenian(jd);

  CHECK(date[0] == 1474);  // Year
  CHECK(date[1] == 11);    // Month
  CHECK(date[2] == 12);    // Day

  CHECK(format_armenian_date_year(jd) == "1474 A.E.");
  CHECK(format_armenian_date_month(jd) == "Margach");
  CHECK(format_armenian_date_day(jd) == "12");
  CHECK(format_armenian_date_weekday(jd) == "Ani");
}

TEST_CASE("Armenian calendar basic functionality") {
  // Test Armenian epoch
  auto epoch_date = jd_to_armenian(ARMENIAN_EPOCH);
  CHECK(epoch_date[0] == 1);
  CHECK(epoch_date[1] == 1);
  CHECK(epoch_date[2] == 1);
}
