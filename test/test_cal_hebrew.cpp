/* 
https://planetcalc.com/8420/

May 2, 2025

Year 5785
Month 2
Month name Iyyar
Day 4

 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_hebrew.h"

TEST_CASE("Hebrew date conversion and formatting") {
  double jd = 2460797.5;  // May 2, 2025

  SUBCASE("Date components valid") {
    auto date = jd_to_hebrew(jd);
    CHECK(date[0] == 5785);
    CHECK(date[1] == 2);
    CHECK(date[2] == 4);
  }

  SUBCASE("Formatted year") {
    std::string year = format_hebrew_date_year(jd);
    CHECK(year.find("AM") != std::string::npos);
  }

  SUBCASE("Formatted month name") {
    std::string month = format_hebrew_date_month(jd);
    CHECK(month == "Iyyar");
  }

  SUBCASE("Formatted weekday") {
    std::string weekday = format_hebrew_date_weekday(jd);
    CHECK(weekday == "Yom Shishi");
  }
}
