#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calendar.h"
#include "cal_hebrew.h"
#include "cal_darian.h"
#include "cal_babylonian.h"
// etc.

// Paste all TEST_CASEs from each test_*.cpp here
// Babylonian
TEST_CASE("Babylonian calendar date conversion") {
  double jd = 2460797.5;  // Example: May 2, 2025
  auto date = jd_to_babylonian(jd);

  CHECK(date[1] >= 1);  // Month is valid
  CHECK(date[2] >= 1);  // Day is valid

  std::string month = babylonian_date_string(jd);
  CHECK(month.find("Nisannu") != std::string::npos || month.find("Ayaru") != std::string::npos);  // Example month names
}

TEST_CASE("Hebrew date full conversion") {
  double jd = 2460807.5;  // May 12, 2025
  CHECK(format_hebrew_date_month(jd) == "Iyyar");
  CHECK(format_hebrew_date_year(jd).find("5785") != std::string::npos);
}

int main(int argc, char **argv) {
  doctest::Context context;
  context.applyCommandLine(argc, argv);
  int res = context.run();
  return res;
}
