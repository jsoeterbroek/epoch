#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include <iostream>
#include "cal_hindu.h"

/*
https://planetcalc.com/9166/
True lunisolar calendar

Year  Month Month name  Day
2082	2	    Vaisakha	  23		
*/

TEST_CASE("hindu calendar date conversion and formatting for May 20, 2025") {
  double jd = gregorian_to_jd(2025, 5, 20);
  auto date = jd_to_hindu_lunar(jd);
  CHECK(date[0] == 2082);
  CHECK(date[2] == 23);
  CHECK(format_hindu_date_day(jd) == "23 (Ashtami)");
  CHECK(format_hindu_date_weekday(jd) == "Mangala-vara");
  CHECK(format_hindu_date_month(jd) == "Vaisakha");
  CHECK(format_hindu_date_year(jd) == "2082");
}

// Test for Diwali
// https://holidaytoday.in/en/india/holidays/diwali-deepavali
//
// Last Year: Thu, 31 Oct 2024
// This Year: Mon, 20 Oct 2025
// Next Year: Sun, 8 Nov 2026
// TEST_CASE("hindu calendar festival: diwali on 31 oct 2024") {
//   double jda = gregorian_to_jd(2024, 10, 31);
//   CHECK(is_hindu_festival(jda, "Diwali"));
// }
// TEST_CASE("hindu calendar festival: diwali on 20 oct 2025") {
//   double jda = gregorian_to_jd(2025, 10, 20);
//   CHECK(is_hindu_festival(jda, "Diwali"));
// }
// TEST_CASE("hindu calendar festival: diwali on 8 nov 2026") {
//   double jda = gregorian_to_jd(2026, 11, 8);
//   CHECK(is_hindu_festival(jda, "Diwali"));
//}

// Test for Holi
// https://holidaytoday.in/en/india/holidays/holi
// Last Year: Mon, 25 Mar 2024
// This Year: Fri, 14 Mar 2025
// Next Year: Wed, 4 Mar 2026
// TEST_CASE("hindu calendar festival: holi on 25 mar 2024") {
//   double jda = gregorian_to_jd(2024, 3, 25);
//   CHECK(is_hindu_festival(jda, "Holi"));
// }
// TEST_CASE("hindu calendar festival: holi on 14 mar 2025") {
//   double jda = gregorian_to_jd(2025, 3, 14);
//   CHECK(is_hindu_festival(jda, "Holi"));
// }
// TEST_CASE("hindu calendar festival: holi on 4 mar 2026") {
//   double jda = gregorian_to_jd(2026, 3, 4);
//   CHECK(is_hindu_festival(jda, "Holi"));
// }
