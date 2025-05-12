#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_hebrew.h"

TEST_CASE("Hebrew calendar modular formatting") {
  double jd = 2460797.5;  // May 2, 2025

  SUBCASE("Day format") {
    std::string day = format_hebrew_date_day(jd);
    CHECK(day.find("Day") != std::string::npos);
  }

  SUBCASE("Month format") {
    std::string month = format_hebrew_date_month(jd);
    CHECK_FALSE(month.empty());
  }

  SUBCASE("Year format") {
    std::string year = format_hebrew_date_year(jd);
    CHECK(year.find("Year") != std::string::npos);
  }

  SUBCASE("Weekday format") {
    std::string weekday = format_hebrew_date_weekday(jd);
    CHECK(weekday.find("Yom") != std::string::npos || weekday == "Shabbat");
  }

  SUBCASE("Full date format") {
    std::string full = format_hebrew_full_date(jd);
    CHECK(full.find(",") != std::string::npos);
  }
}

TEST_CASE("Hebrew to JD conversion") {
  SUBCASE("14 Iyyar 5785 = 2460807.5") {
    double expected_jd = 2460807.5;
    double calculated_jd = hebrew_to_jd(5785, 8, 14);

    CHECK(std::abs(calculated_jd - expected_jd) < 0.5);  // Allow 0.5 day rounding
  }
}

TEST_CASE("Hebrew month name is Iyyar on 2025-05-12") {
  double jd = 2460807.5;

  std::string month = format_hebrew_date_month(jd);

  CHECK(month == "Iyyar");
}
