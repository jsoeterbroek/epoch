/* https://planetcalc.com/8500/
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_coptic.h"

TEST_CASE("Coptic date conversion and formatting") {
  double jd = 2460797.5;  // May 2, 2025

  SUBCASE("Date components valid") {
    auto date = jd_to_coptic(jd);
    CHECK(date[0] > 1700);
    CHECK(date[1] >= 1);
    CHECK(date[1] <= 13);
    CHECK(date[2] >= 1);
    CHECK(date[2] <= 30);
  }

  SUBCASE("Formatted year") {
    std::string year = format_coptic_date_year(jd);
    CHECK(year.find("AM") != std::string::npos);
  }

  SUBCASE("Formatted month name liturgical") {
    std::string month = format_coptic_date_month(jd, CopticMonthVariant::Liturgical);
    CHECK(month == "Baramouda");
  }

  SUBCASE("Formatted month name academic") {
    std::string month = format_coptic_date_month(jd, CopticMonthVariant::Academic);
    CHECK(month == "Paremoude");
  }

  SUBCASE("Formatted weekday liturgical") {
    std::string weekday = format_coptic_date_weekday(jd, CopticWeekdayVariant::Liturgical);
    CHECK(weekday == "Paraskevi");  // Friday
  }
}
