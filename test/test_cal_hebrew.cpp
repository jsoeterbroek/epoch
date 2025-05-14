#include <unity.h>
#include "cal_hebrew.h"

void test_hebrew_date_formatting(void) {
  double jd = 2460797.5;  // Example JD, adjust as needed
  std::string year = format_hebrew_date_year(jd);
  std::string month = format_hebrew_date_month(jd);
  std::string day = format_hebrew_date_day(jd);

  TEST_ASSERT_NOT_EQUAL(-1, (int)year.find("Year"));
  TEST_ASSERT_NOT_EQUAL(-1, (int)month.find("Month"));
  TEST_ASSERT_NOT_EQUAL(-1, (int)day.find("Day"));
}
