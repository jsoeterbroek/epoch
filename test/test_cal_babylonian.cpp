// test/test_babylonian.cpp
#include "unity.h"
#include "cal_babylonian.h"

void test_babylonian_calendar_date_conversion(void) {
  double jd = 2460402.5;  // April 1, 2024
  auto date = jd_to_babylonian(jd);
  TEST_ASSERT_TRUE(date[0] >= 2334);
  TEST_ASSERT_TRUE(date[1] >= 1);
  TEST_ASSERT_TRUE(date[2] >= 1);

  std::string date_str = format_babylonian_date(jd);
  std::string weekday_str = format_babylonian_date_weekday(jd);

  TEST_ASSERT_NOT_EQUAL(-1, (int)date_str.find("Nisannu"));
  TEST_ASSERT_FALSE(weekday_str.empty());
}

void test_babylonian_intercalary_year_addaru_ii(void) {
  double jd = 2461450.5;  // ~ March 1, 2027
  auto date = jd_to_babylonian(jd);

  std::string month_name = format_babylonian_date_month(jd);
  TEST_ASSERT_TRUE(month_name.find("Addaru II") != std::string::npos || month_name.find("Addaru") != std::string::npos);
}

void test_babylonian_intercalary_year_ululu_ii(void) {
  double jd = 2461278.5;  // ~ September 10, 2026
  auto date = jd_to_babylonian(jd);

  std::string month_name = format_babylonian_date_month(jd);
  TEST_ASSERT_TRUE(month_name.find("Ululu II") != std::string::npos || month_name.find("Ululu") != std::string::npos);
}
