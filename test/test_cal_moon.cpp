#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include <iostream>

/*
https://stardate.org/moon-phase-calculator
2025-05-4 - First Quarter
2025-05-12 - Full Moon
2025-05-21 - Waning Crescent
Volle maan	30 juni 2026
2008-09-18 - Waning Gibbous
 */

//2025-05-4 - First Quarter
TEST_CASE("Moon phase for 2025-05-4 First Quarter") {
  double mjd1 = gregorian_to_jd(2025, 5, 4);
  std::string cpp_str1 = calendar::format_moon_phase(mjd1);
  String moonStr1 = String(cpp_str1.c_str());
  CHECK(moonStr1 == "First Quarter");
}

// 2025-05-12 - Full Moon
TEST_CASE("Moon phase for 2025-05-12 Full Moon") {
  double mjd2 = gregorian_to_jd(2025, 5, 21);
  std::string cpp_str2 = calendar::format_moon_phase(mjd2);
  String moonStr2 = String(cpp_str2.c_str());
  CHECK(moonStr2 == "Full Moon");
}

// 2025-05-21 - Waning Crescent
TEST_CASE("Moon phase for 2025-05-21 Waning Crescent") {
  double mjd3 = gregorian_to_jd(2025, 5, 21);
  std::string cpp_str3 = calendar::format_moon_phase(mjd3);
  String moonStr3 = String(cpp_str3.c_str());
  CHECK(moonStr3 == "Waning Crescent");
}

// 2025-03-29 New Moon
TEST_CASE("Moon phase for 2025-03-29 New Moon") {
  double mjd5 = gregorian_to_jd(2025, 3, 29);
  std::string cpp_str5 = calendar::format_moon_phase(mjd5);
  String moonStr5 = String(cpp_str5.c_str());
  CHECK(moonStr5 == "New Moon");
}
