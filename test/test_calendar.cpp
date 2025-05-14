#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "calendar.h"

// TEST_CASE ...
TEST_CASE("Test Calendar Class") {
  Calendar calendar;

  // Test the default constructor
  CHECK(calendar.getYear() == 2023);
  CHECK(calendar.getMonth() == 1);
  CHECK(calendar.getDay() == 1);

  // Test the parameterized constructor
  Calendar customCalendar(2022, 12, 25);
  CHECK(customCalendar.getYear() == 2022);
  CHECK(customCalendar.getMonth() == 12);
  CHECK(customCalendar.getDay() == 25);

  // Test the setDate method
  calendar.setDate(2024, 7, 4);
  CHECK(calendar.getYear() == 2024);
  CHECK(calendar.getMonth() == 7);
  CHECK(calendar.getDay() == 4);
}
// TEST_SUITE ...

int main(int argc, char **argv) {
  doctest::Context context;

  // BEGIN:: PLATFORMIO REQUIRED OPTIONS
  context.setOption("success", true);      // Report successful tests
  context.setOption("no-exitcode", true);  // Do not return non-zero code on failed test case
  // END:: PLATFORMIO REQUIRED OPTIONS

  // YOUR CUSTOM DOCTEST OPTIONS

  context.applyCommandLine(argc, argv);
  return context.run();
}
