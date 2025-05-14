#include "unity.h"
#include "cal_chinese_zodiac.h"

void test_chinese_zodiac_full_date_formatting(void) {
  double jd = 2460797.5;  // 2025-05-02
  std::string result = format_chinese_zodiac_full_date(jd);

  TEST_ASSERT_NOT_EQUAL(-1, (int)result.find("Yi-Si"));   // Year stem-branch
  TEST_ASSERT_NOT_EQUAL(-1, (int)result.find("Sanyue"));  // Lunar month
  TEST_ASSERT_NOT_EQUAL(-1, (int)result.find("Snake"));   // Zodiac animal
  TEST_ASSERT_NOT_EQUAL(-1, (int)result.find("-"));       // Day stem-branch
}
