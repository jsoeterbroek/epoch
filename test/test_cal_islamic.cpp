/*
18 may 2025

-------
https://datehijri.com/en/

Sunday, Dhu al-Qidah 20, 1446 AH
20/11/1446
Is it leap year:	2025 It's not leap year
--------------
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_islamic.h"
#include "cal_gregorian.h"
#include <iostream>

TEST_CASE("Islamic calendar date conversion and formatting for may 18, 2025") {
  double jd1 = gregorian_to_jd(2025, 5, 18);
  auto date1 = jd_to_islamic(jd1);
  CHECK(date1[0] == 1446);
  CHECK(date1[1] == 11);
  CHECK(date1[2] == 20);
  CHECK(format_islamic_date_day_local(jd1, false) == "20");
  CHECK(format_islamic_date_weekday_local(jd1, false) == "al-Ahad");
  CHECK(format_islamic_date_month_local(jd1, false) == "Dhu al-Qidah");
  CHECK(format_islamic_date_year_local(jd1, false) == "1446 AH");
}

/* 
--------------
https://en.wikipedia.org/wiki/File:King_Khaled_airport_exit_stamp.jpg
10 Rajab 1428 AH (24 July 2007 CE)

https://timesprayer.com/en/dateconverter.html
10 Rajab 1428  = Tuesday 24 July 2007
-------------- 
*/
TEST_CASE("Islamic calendar date conversion and formatting for july 24, 2007") {
  double jd2 = gregorian_to_jd(2007, 7, 24);
  CHECK(format_islamic_date_month_local(jd2, false) == "Rajab");
  CHECK(format_islamic_date_year_local(jd2, false) == "1428 AH");
}

TEST_CASE("Islamic calendar date conversion leap year check") {
  CHECK(islamic_is_leap_year(1446) == 0);
  CHECK(islamic_is_leap_year(1445) == 1);  // 1445 is a leap year
  CHECK(islamic_is_leap_year(1444) == 0);
  CHECK(islamic_is_leap_year(1443) == 0);
}
