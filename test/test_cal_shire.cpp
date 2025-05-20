#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include <iostream>
#include "cal_shire.h"

/* 
| S.R. Year | Afteryule 1 | Gregorian Date | JD        |
| --------- | ----------- | -------------- | --------- |
| 1         | 1601-01-02  | 1601-01-02     | 2305814.5 |
| 1421      | 2021-01-02  | 2021-01-02     | 2459216.5 | 
*/
// TEST_CASE("Shire calendar conversion table for shire years 1 and 1421") {
//   // Afteryule 1, S.R. 1 is Gregorian Jan 2, 1601 (2305814.5 JD)
//   double jd_1 = shire_to_jd(1, 1, 1);
//   auto gdate_1 = jd_to_gregorian(jd_1);
//   //auto sdate_1 = jd_to_shire(jd_1);
//   CHECK(gdate_1[0] == 1601);
//   // Afteryule 1, S.R. 1421 is Gregorian Jan 2, 2021 (2459216.5 JD)
//   double jd_1421 = shire_to_jd(1421, 1, 1);
//   auto gdate_1421 = jd_to_gregorian(jd_1421);
//   //auto sdate_1421 = jd_to_shire(jd_1421);
//   CHECK(gdate_1421[0] == 2021);
// }

// TEST_CASE("Shire calendar conversion with Afteryule 1, S.R. 1421") {
//   // Afteryule 1, S.R. 1421 is Gregorian Jan 2, 2021
//   double jd = shire_to_jd(1421, 1, 1);
//   //   auto gdate = jd_to_gregorian(jd);
//   //   std::cout << "Gregorian: " << gdate[0] << "-" << gdate[1] << "-" << gdate[2] << std::endl;
//   //   auto sdate = jd_to_shire(jd);
//   //   CHECK(gdate[0] == 2021);
//   //   CHECK(sdate[0] == 1421);
//   //   CHECK(sdate[1] == 1);
//   //   CHECK(sdate[2] == 1);
//   CHECK(format_shire_date_year(jd) == "1421 S.R.");
//   //   CHECK(format_shire_date_month(jd) == "Afteryule");
//   //   CHECK(format_shire_date_day(jd) == "1");
//   //   CHECK(!format_shire_date_weekday(jd).empty());
// }

/* 
https://time-meddler.co.uk/the-shire-calendar/
Trewsday 30 Thrimidge
TEST_CASE("Shire calendar date conversion and formatting for May 20, 2025") {
  double jd = gregorian_to_jd(2025, 5, 20);
  //auto date = jd_to_shire(jd);
  //CHECK(date[0] == 5);
  //CHECK(date[1] == 5);
  //CHECK(date[2] == 30);
  CHECK(format_shire_date_day(jd) == "30");
  CHECK(format_shire_date_weekday(jd) == "Trewsday");
  CHECK(format_shire_date_month(jd) == "Thrimidge");
  //CHECK(format_shire_date_year(jd) == "1947");
}

 */
