/* 
https://www.napoleon-empire.org/en/republican-calendar.php
The 17 May 1805 corresponds to 27 Floréal Year XIII
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_rev_french.h"
#include "cal_gregorian.h"

TEST_CASE("French revolutionary calendar returns for 17th of may 1805") {
  double jd = gregorian_to_jd(1805, 05, 17);
  CHECK(format_french_date_month(jd) == "Floreal");
  CHECK(format_french_date_month_description(jd) == "Month of flowering");
  CHECK(format_french_date_weekday(jd) == "Primidi");
  CHECK(format_french_date_day(jd) == "27");
  CHECK(format_french_date_year(jd) == "XIII AN");
}
