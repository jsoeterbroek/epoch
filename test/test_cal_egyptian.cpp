#include "unity.h"
#include "cal_egyptian.h"

void test_egyptian_date_formatting(void) {
  double jd = 2460797.5;  // Example JD, adjust as needed
  std::string year = format_egyptian_date_year(jd);
  std::string month = format_egyptian_date_month(jd);
  std::string day = format_egyptian_date_day(jd);

  TEST_ASSERT_NOT_EQUAL(-1, (int)year.find("Year"));
  TEST_ASSERT_NOT_EQUAL(-1, (int)month.find("Month"));
  TEST_ASSERT_NOT_EQUAL(-1, (int)day.find("Day"));
}
