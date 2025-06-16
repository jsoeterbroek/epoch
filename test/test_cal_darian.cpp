#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_darian.h"
#include "cal_gregorian.h"
#include <iostream>

// https://interimm.org/mars-clock/en/
// TEST_CASE("Darian (Mars) calendar date conversion and formatting") {
//   double jd = gregorian_to_jd(2025, 5, 20);
//   int darian_year, darian_month, sol;
//   jd_to_darian(jd, darian_year, darian_month, sol);
// }

/*
Some important dates in the Darian calendar (Source: https://en.wikipedia.org/wiki/Darian_calendar):

+----------------------+-------------------+--------------------+-----------------+---------------+
| Event                | Gregorian date    | Darian date 	      | Mars Julian Sol | Mars Sol Date |
+----------------------+-------------------+--------------------+-----------------+---------------+
| Mariner 4 flyby      | 15 July 1965      | 26 Taurus 189      | 126668 	        | 32539         |
| Viking 1 landing     | 20 July 1976 		 | 14 Mina 195        | 130584 	        | 36455         |
| Viking 2 landing 	   | 3 September 1976  | 3 Mesha 195        | 130629          | 36500         |
| Perseverance landing | 18 February 2021  | 13 Sagittarius 219 | 146433 	        | 52304         |
+----------------------+-------------------+--------------------+-----------------+---------------+
*/

// Mariner 4 flyby: 15 July 1965 = 26 Taurus 189 in Darian calendar
// TEST_CASE("Mariner 4 flyby date conversion") {
//   double jd1 = gregorian_to_jd(1965, 7, 15);
//   int darian_year, darian_month, sol;
//   jd_to_darian(jd1, darian_year, darian_month, sol);
//   CHECK(format_darian_date_full(darian_year, darian_month, sol, DarianWeekStyle::Latin, DarianMonthStyle::Zodiac) == "Taurus 26, 189 ME, Sol Solis");
// }

// // Perseverance landing: 18 February 2021  = 13 Sagittarius 219 in Darian calendar
// TEST_CASE("Perseverance landing date conversion") {
//   double jd2 = gregorian_to_jd(2021, 2, 18);
//   int darian_year, darian_month, sol;
//   jd_to_darian(jd2, darian_year, darian_month, sol);
//   CHECK(format_darian_date_full(darian_year, darian_month, sol, DarianWeekStyle::Latin, DarianMonthStyle::Zodiac) == "Sagittarius 13, 219 ME, Sol Solis");
// }
