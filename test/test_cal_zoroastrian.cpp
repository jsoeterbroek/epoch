/* 

For Gregorian 18 may 2025:
-----------------------------------------------------
https://theparsidirectory.com/date.html


Calender	Date	      Mah	          Roj
--------  ----	      ---         	---
Fasli 	  29/2/1394 	Ardibehesht 	Mareshpand
Kadmi 	  7/11/1394 	Bahman 	      Amardad
Shenshai 	7/10/1394 	Dae 	        Amardad

-----------------------------------------------------
https://zanc.org/zcal/zcal.html

Fasli     Mareshpand (Ardibehesht)
Kadmi 	  Amardad (Bahman)
Shenshai 	Amardad (Dae)

-----------------------------------------------------
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_zoroastrian.h"
#include "cal_gregorian.h"

// Fasli is default zoroastrian cal in Epoch
// FIXME: add more test cases for other variants, eg. nowroz

TEST_CASE("Zoroastrian Fasli calendar date conversion and formatting for May 18, 2025") {
  double jd = gregorian_to_jd(2025, 05, 18);

  SUBCASE("Date components are valid") {
    // Fasli 	  29/2/1394
    auto date = jd_to_zoroastrian(jd, ZoroastrianCalendarVariant::Fasli);
    CHECK(date[0] == 1394);
    CHECK(date[1] == 2);
    CHECK(date[2] == 29);
  }

  SUBCASE("Formatted month (mah)") {
    std::string month = format_zoroastrian_date_mah(jd, ZoroastrianCalendarVariant::Fasli);
    CHECK(month == "Ardibehesht");  // 2025-05-18 is in Ardibehesht month
  }

  SUBCASE("Formatted weekday (roj)") {
    std::string weekday = format_zoroastrian_date_roj(jd, ZoroastrianCalendarVariant::Fasli);
    CHECK(weekday == "Mareshpand");  // 2025-05-12 is a Monday
  }
}
