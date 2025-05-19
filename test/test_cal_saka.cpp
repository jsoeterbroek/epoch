#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_saka.h"
#include "cal_gregorian.h"
#include <iostream>

/*
-------
Monday, 19 May, 2025
https://planetcalc.com/9142/
Year 1947
Month 2
Month name Vaisakha
Day 29
--------------
*/
TEST_CASE("Saka calendar date conversion and formatting for may 19, 2025") {
  double jd = gregorian_to_jd(2025, 5, 19);
  auto date = jd_to_saka(jd);
  CHECK(date[0] == 1947);
  CHECK(date[1] == 2);
  CHECK(date[2] == 29);
  CHECK(format_saka_date_day(jd) == "29");
  CHECK(format_saka_date_weekday_local(jd, false) == "Somavara");
  CHECK(format_saka_date_month_local(jd, false) == "Vaishakha");
  CHECK(format_saka_date_year_local(jd, false) == "1947");
}

/* 
-------
https://en.wikipedia.org/wiki/Indian_national_calendar#/media/File:Gazette_notification_by_Govt._of_India.jpg
july 12, 2024 / Ashadha 21, 1946
------- 
*/
TEST_CASE("Saka calendar date conversion and formatting for july 12, 2024") {
  double jd = gregorian_to_jd(2024, 7, 12);
  CHECK(format_saka_date_day(jd) == "21");
  CHECK(format_saka_date_month_local(jd, false) == "Ashadha");
  CHECK(format_saka_date_year_local(jd, false) == "1946");
}
