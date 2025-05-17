#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_icelandic.h"
#include <string>

// TEST_CASE("Icelandic calendar matches Time Meddler for known 2025 dates") {
//     struct IcelandicDateTest {
//         double jd;
//         const char* expected_month;
//         int expected_day;
//     };

//     // Based on https://time-meddler.co.uk/the-old-icelandic-calendar/ for 2025
//     IcelandicDateTest test_cases[] = {
//         {2460786.5, "Harpa", 1},      // April 24, 2025
//         {2460787.5, "Harpa", 2},      // April 25, 2025
//         {2460809.5, "Harpa", 24},     // May 17, 2025
//         {2460815.5, "Harpa", 30},     // May 23, 2025
//         {2460816.5, "Skerpla", 1},    // May 24, 2025
//         {2460822.5, "Skerpla", 7},    // May 30, 2025
//     };

//     for (const auto& test : test_cases) {
//         SUBCASE(std::string("JD ") + std::to_string(test.jd)) {
//             CHECK(format_icelandic_date_month(test.jd) == test.expected_month);
//             CHECK(format_icelandic_date_day(test.jd) == "Day " + std::to_string(test.expected_day));
//         }
//     }
// }
