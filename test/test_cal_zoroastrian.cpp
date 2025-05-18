/* 
  NOTE: The Zoroastrian Fasli calendar, as implemented here, is strictly a 365-day solar calendar with no leap years.
  As a result, it "drifts" relative to the Gregorian calendar, gaining nearly one extra day every four years.
  By the year 2025, the Fasli calendar is approximately 10 years ahead of the Gregorian year, 
  and the months/days do not match up with modern Gregorian-aligned versions sometimes used in community practice.
  This test suite uses the historically accurate, original Fasli system (epoch: JD 1948320.5, March 21, 632 CE Gregorian).
  For other variants or for versions kept in sync with the Gregorian calendar, the code and test expectations must be 
  adapted accordingly.
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_zoroastrian.h"
#include "cal_gregorian.h"
#include <iostream>

TEST_CASE("Zoroastrian Fasli calendar date conversion and formatting for May 18, 2025") {
  double jd = 2460475.5;
  //std::cout << "JD for 2025-05-18: " << jd << std::endl;  // should be 2460475.5
  auto date = jd_to_zoroastrian(jd);
  //std::cout << "Zoroastrian date: " << date[0] << "-" << date[1] << "-" << date[2] << std::endl;
  //std::cout << "Day-of-month passed to day_name: " << date[2] << std::endl;
  //std::cout << "Resulting weekday: " << format_zoroastrian_date_weekday(jd) << std::endl;

  CHECK(date[0] == 1404);
  CHECK(date[1] == 3);
  CHECK(date[2] == 1);
  CHECK(format_zoroastrian_date_weekday(jd) == "Hormazd");
  CHECK(format_zoroastrian_date_month(jd) == "Khordad");
  CHECK(format_zoroastrian_date_year(jd) == "1404 YZ");
}
