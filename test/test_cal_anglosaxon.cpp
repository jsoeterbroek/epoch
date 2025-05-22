#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_anglosaxon.h"
#include <iostream>

/*
-------
Thursday, 22 May, 2025
Should be:
Dunresdag, 25th of Thrimilchi 
--------------
*/
TEST_CASE("Anglosaxon calendar date conversion and formatting for may 22, 2025") {
  double jd = gregorian_to_jd(2025, 5, 22);
  CHECK(format_anglosaxon_date_day(jd) == "25");
  CHECK(format_anglosaxon_date_weekday(jd) == "Dunresdag");
  CHECK(format_anglosaxon_date_month(jd) == "Thrimilchi");
}

// Eosturdag - Sun Apr 13, 2025 CE	  15th of Eosturmonath
TEST_CASE("Anglosaxon calendar holiday conversion and formatting for Eosturdag") {
  double jd = gregorian_to_jd(2025, 4, 13);
  CHECK(format_anglosaxon_date_day(jd) == "15");
  CHECK(format_anglosaxon_date_month(jd) == "Eosturmonath");
  CHECK(is_anglosaxon_holiday(jd, "Eosturdag") == true);
}

// Midsumor	- Sat Jun 21, 2025 CE	  25th of Aerra Litha
TEST_CASE("Anglosaxon calendar holiday conversion and formatting for Eosturdag") {
  double jd = gregorian_to_jd(2025, 6, 21);
  CHECK(format_anglosaxon_date_day(jd) == "25");
  CHECK(format_anglosaxon_date_month(jd) == "Aerra Litha");
  CHECK(is_anglosaxon_holiday(jd, "Midsumor") == true);
}
