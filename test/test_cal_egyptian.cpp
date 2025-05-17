#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_egyptian.h"

TEST_CASE("Egyptian civil calendar from Nabonassar epoch") {
  double epoch_jd = 1448638.5;  // Nabonassar accession

  SUBCASE("Epoch = Year 1, Month 1, Day 1") {
    auto date = jd_to_egyptian(epoch_jd);
    CHECK(date[0] == 1);
    CHECK(date[1] == 1);
    CHECK(date[2] == 1);
  }

  SUBCASE("1 year after epoch") {
    auto date = jd_to_egyptian(epoch_jd + 365);
    CHECK(date[0] == 2);
    CHECK(date[1] == 1);
    CHECK(date[2] == 1);
  }

  SUBCASE("Formatted date") {
    double jd = epoch_jd + (3 * 365) + (5 * 30) + 9;  // Year 4, Month 6, Day 10
    CHECK(format_egyptian_date_weekday(jd) == "Day 3");
    CHECK(format_egyptian_date_day(jd) == "hmnw-hry");
    CHECK(format_egyptian_date_month(jd) == "Month 6");
    CHECK(format_egyptian_date_year(jd) == "Year 4");
  }
}

//TEST_CASE("Regnal year formatting") {
//  SUBCASE("Ramses II start") {
//    double jd = 1202673.5;  // Approx. accession of Ramses II
//    std::string regnal = format_egyptian_regnal_year(jd);
//    CHECK(regnal.find("Year 1 of Ramses II") != std::string::npos);
//  }

//  SUBCASE("Ramses II later date") {
//    double jd = 1202673.5 + 10 * 365;
//    std::string regnal = format_egyptian_regnal_year(jd);
//    CHECK(regnal.find("Year 11 of Ramses II") != std::string::npos);
//  }

//  SUBCASE("Unknown regnal period") {
//    double jd = 1000000.5;
//    CHECK(format_egyptian_regnal_year(jd) == "Unknown regnal year");
//  }
//}
