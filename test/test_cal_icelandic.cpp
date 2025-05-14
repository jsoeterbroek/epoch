#include <unity.h>
#include "cal_icelandic.h"

void test_year_format(void) {
  double jd = 2460807.5;  // May 12, 2025
  std::string year = format_icelandic_date_year(jd);
  TEST_ASSERT_NOT_EQUAL(-1, (int)year.find("Year"));
}

void test_month_format(void) {
  double jd = 2460807.5;  // May 12, 2025
  std::string month = format_icelandic_date_month(jd);
  TEST_ASSERT_EQUAL_STRING("Solmanuthur", month.c_str());
}

void test_day_format(void) {
  double jd = 2460807.5;  // May 12, 2025
  std::string day = format_icelandic_date_day(jd);
  TEST_ASSERT_NOT_EQUAL(-1, (int)day.find("Day"));
}

void test_weekday_format(void) {
  double jd = 2460807.5;  // May 12, 2025
  std::string weekday = format_icelandic_date_weekday(jd);
  TEST_ASSERT_EQUAL_STRING("Manudagur", weekday.c_str());
}
