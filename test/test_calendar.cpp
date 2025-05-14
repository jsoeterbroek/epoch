#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"

TEST_CASE("mod and amod utility functions") {
  SUBCASE("mod() with positive values") {
    CHECK(mod(10.0, 7.0) == doctest::Approx(3.0));
  }

  SUBCASE("mod() with negative values") {
    CHECK(mod(-1.0, 7.0) == doctest::Approx(6.0));
  }

  SUBCASE("amod() with positive values") {
    CHECK(amod(1.0, 7.0) == doctest::Approx(1.0));
    CHECK(amod(8.0, 7.0) == doctest::Approx(1.0));
  }

  SUBCASE("amod() with negative values") {
    CHECK(amod(-1.0, 7.0) == doctest::Approx(6.0));
  }
}

TEST_CASE("Julian Day Epoch Constants") {
  CHECK(GREGORIAN_EPOCH == doctest::Approx(1721425.5));  // Example: 0001-01-01 Gregorian
  CHECK(HEBREW_EPOCH == doctest::Approx(347995.5));      // 1 Tishrei AM 1
}
