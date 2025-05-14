#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_chinese_zodiac.h"

TEST_CASE("Chinese Zodiac full date formatting") {
  // JD for 2025-05-02
  double jd = 2460797.5;

  std::string result = format_chinese_zodiac_full_date(jd);

  CHECK(result.find("Yi-Si") != std::string::npos);   // Year stem-branch
  CHECK(result.find("Sanyue") != std::string::npos);  // Lunar month
  CHECK(result.find("Snake") != std::string::npos);   // Zodiac animal
  CHECK(result.find("-") != std::string::npos);       // Day stem-branch
}
