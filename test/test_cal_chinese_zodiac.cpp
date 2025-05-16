/* 

https://pteo.paranoiaworks.mobi/chinese_calendar/

Chinese Date: 2025/04/05 (year/month/day)
Leap Month: No
Chinese Year Name: 乙巳 (Yi Si)
Chinese Year Sign: 蛇 (Snake)
Cosmic Element: 木 (Wood)
Ming: 佛灯火 (Lamp Fire)
Day of Week: 星期五 (Friday)

Chinese Date:	Xin-Si (Snake) (4th month), 5, 4723

*/
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_chinese_zodiac.h"

TEST_CASE("Chinese Zodiac full date formatting") {
  // JD for 2025-05-02
  double jd = 2460797.5;

  std::string result = format_chinese_zodiac_full_date(jd);

  CHECK(result.find("Yi-Si") != std::string::npos);  // Year stem-branch
  CHECK(result.find("Snake") != std::string::npos);  // Zodiac animal
}

TEST_CASE("Chinese Zodiac date conversion and formatting") {

  double jd = 2460797.5;  // May 2, 2025

  SUBCASE("Day stem-branch") {
    std::string day_stem_branch = chinese_day_stem_branch(jd);
    CHECK(day_stem_branch == "Geng-Zi");
  }

  SUBCASE("Formatted lunar month name") {
    std::string lunar_month_name = chinese_lunar_month_name(jd);
    CHECK(lunar_month_name == "Siyue");
  }

  SUBCASE("Formatted year name") {
    std::string year = format_chinese_zodiac_date_year(jd);
    CHECK(year == "Yi-Si");
  }

  SUBCASE("Year zodiac animal") {
    std::string sign = chinese_zodiac_animal(jd);
    CHECK(sign == "Snake");
  }
}
