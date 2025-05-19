#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_buddhist.h"
#include <iostream>

/*
-------
Monday, 19 May, 2025
--------------
*/

TEST_CASE("Buddhist (Thai Solar) calendar conversion and formatting for May 18, 2025") {
  double jd = gregorian_to_jd(2025, 5, 18);

  auto bdate = jd_to_buddhist(jd);
  CHECK(bdate[0] == 2568);  // 2025 + 543
  CHECK(bdate[1] == 5);     // May
  CHECK(bdate[2] == 18);    // 18th

  CHECK(format_buddhist_date(bdate) == "2568-5-18 (May)");
  CHECK(format_buddhist_date_day(jd) == "18");
  CHECK(format_buddhist_date_weekday(jd) == "Sunday");
  CHECK(format_buddhist_date_month(jd) == "May");
  CHECK(format_buddhist_date_year(jd) == "2568 BE");
}
