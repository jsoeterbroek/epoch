/* // https://planetcalc.com/8504/
// 12 may 2025:
Year 2017
Month 9
Month name Gənbot
Day 4
Week day name Sanyo 
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_ethiopian.h"

TEST_CASE("Ethiopian calendar date conversion and formatting") {
  double jd = 2460807.5;  // May 12, 2025

  SUBCASE("Date components are valid") {
    auto date = jd_to_ethiopian(jd);
    CHECK(date[0] > 1700);
    CHECK(date[1] >= 1);
    CHECK(date[1] <= 13);
    CHECK(date[2] >= 1);
    CHECK(date[2] <= 30);
  }

  SUBCASE("Formatted month") {
    std::string month = format_ethiopian_date_month(jd);
    CHECK(month == "Genbot");
  }

  SUBCASE("Formatted weekday") {
    std::string weekday = format_ethiopian_date_weekday(jd);
    CHECK(weekday == "Monday");  // 2025-05-12 is a Monday
  }
}
