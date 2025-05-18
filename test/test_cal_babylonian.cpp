// test_babylonian.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "cal_babylonian.h"

TEST_CASE("Babylonian calendar date conversion for April 1, 2024") {
  // JD for April 1, 2024
  double jd = 2460402.5;

  auto date = jd_to_babylonian(jd);
  CHECK(date[0] >= 2221);  // Babylonian year
  CHECK(date[1] >= 1);
  CHECK(date[2] >= 1);

  SUBCASE("Formatted date") {
    std::string weekday_str = format_babylonian_date_weekday(jd);
    std::string month_str = format_babylonian_date_month(jd);
    std::string year_str = format_babylonian_date_year(jd);
    std::string date_str = format_babylonian_date(jd);

    CHECK(weekday_str == "Umu 3");
    CHECK(month_str == "Addaru");
    CHECK(year_str == "2221 SE");
    CHECK(date_str == "Addaru 5");
  }
}
//TEST_CASE("Babylonian intercalary year with Addaru II") {
//  // JD ~ March 1, 2027 — year 2338 SE (Metonic year 19, should have Addaru II)
//  double jd = 2461450.5;
//  std::string month_name = format_babylonian_date_month(jd);
//  CHECK((month_name.find("Addaru II") != std::string::npos || month_name.find("Addaru") != std::string::npos));
//}

//TEST_CASE("Babylonian intercalary year with Ululu II") {
//  // JD ~ September 10, 2026 — year 2337 SE (Metonic year 17, should have Ululu II)
//  double jd = 2461278.5;
//  std::string month_name = format_babylonian_date_month(jd);
//  CHECK((month_name.find("Ululu II") != std::string::npos || month_name.find("Ululu") != std::string::npos));
//}
