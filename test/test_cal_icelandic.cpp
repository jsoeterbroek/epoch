/* 
According to https://time-meddler.co.uk/the-old-icelandic-calendar/
the gregorian date of 2025-05-17 is
Laugardagr
24
Harpa
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_icelandic.h"
#include "cal_gregorian.h"

TEST_CASE("Icelandic calendar returns for 17th of may 2025") {
  double jd = gregorian_to_jd(2025, 05, 17);
  CHECK(format_icelandic_date_month(jd) == "Harpa");
  CHECK(format_icelandic_date_month_description(jd) == "First summer month");
  CHECK(format_icelandic_date_weekday(jd) == "Laugardagur");
  CHECK(format_icelandic_date_day(jd) == "27");
}

TEST_CASE("Icelandic calendar returns for known year within table") {
  double jd = 2461037.5;  // Year well inside defined range
  CHECK(format_icelandic_date_month(jd) == "Thorri");
  CHECK(format_icelandic_date_month_description(jd) == "Fat-sucking month - harsh winter begins");
}

TEST_CASE("Icelandic calendar returns for known year within table 2") {
  double jd = 2460947.5;  // Year well inside defined range
  CHECK(format_icelandic_date_month(jd) == "Gormanuthur");
  CHECK(format_icelandic_date_month_description(jd) == "Autumn month - gathering and storing begins");
}
