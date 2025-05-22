#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_anglosaxon.h"
#include <iostream>

/* 
Different reconstructions of the Old English calendar pick slightly different “month‐start” dates. 
The version here implemented has Thrimilci beginning on April 24 (so May 22 → day 29), whereas 
Mine Wyrtruman’s calendar apparently begins Thrimilci on April 28 (or thereabouts), which makes 
May 22 only the 25th.

Scholars don’t all agree on the precise day each month began—some tie month-starts to fixed equinox 
dates, others to ecclesiastical reckonings—so you’ll see these 3–4-day offsets in different 
reconstructions. Neither is “wrong”.
 */
/*
-------
Thursday, 22 May, 2025
--------------
*/
TEST_CASE("Anglosaxon calendar date conversion and formatting for may 22, 2025") {
  double jd = gregorian_to_jd(2025, 5, 22);
  CHECK(format_anglosaxon_date_day(jd) == "29");
  CHECK(format_anglosaxon_date_weekday(jd) == "Dunresdag");
  CHECK(format_anglosaxon_date_month(jd) == "Thrimilchi");
}

// // Eosturdag - Sun Apr 13, 2025 CE	  15th of Eosturmonath
// TEST_CASE("Anglosaxon calendar holiday conversion and formatting for Eosturdag") {
//   double jd = gregorian_to_jd(2025, 4, 13);
//   CHECK(format_anglosaxon_date_day(jd) == "15");
//   CHECK(format_anglosaxon_date_month(jd) == "Eosturmonath");
//   CHECK(is_anglosaxon_holiday(jd, "Eosturdag") == true);
// }

// // Midsumor	- Sat Jun 21, 2025 CE	  25th of Aerra Litha
// TEST_CASE("Anglosaxon calendar holiday conversion and formatting for Eosturdag") {
//   double jd = gregorian_to_jd(2025, 6, 21);
//   CHECK(format_anglosaxon_date_day(jd) == "25");
//   CHECK(format_anglosaxon_date_month(jd) == "Aerra Litha");
//   CHECK(is_anglosaxon_holiday(jd, "Midsumor") == true);
// }
