#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_icelandic.h"

TEST_CASE("Icelandic calendar formatting for May 12, 2025") {
  double jd = 2460807.5;  // May 12, 2025

  SUBCASE("Year format") {
    std::string year = format_icelandic_date_year(jd);
    CHECK(year.find("Year") != std::string::npos);
  }

  SUBCASE("Month format") {
    std::string month = format_icelandic_date_month(jd);
    CHECK(month == "Sólmánuður");
  }

  SUBCASE("Day format") {
    std::string day = format_icelandic_date_day(jd);
    CHECK(day.find("Day") != std::string::npos);
  }

  SUBCASE("Weekday format") {
    std::string weekday = format_icelandic_date_weekday(jd);
    CHECK(weekday == "Mánudagur");
  }
}
