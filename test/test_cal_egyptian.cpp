#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "cal_egyptian.h"

TEST_CASE("Egyptian calendar formatting") {
    double jd = 2460797.5; // May 2, 2025

    SUBCASE("Day format") {
        std::string day = format_egyptian_date_day(jd);
        CHECK(day.find("Day") != std::string::npos);
    }

    SUBCASE("Month format") {
        std::string month = format_egyptian_date_month(jd);
        CHECK(month == "Phaophi");
    }

    SUBCASE("Year format") {
        std::string year = format_egyptian_date_year(jd);
        CHECK(year.find("Year") != std::string::npos);
    }

    SUBCASE("Weekday (Decan) format") {
        std::string weekday = format_egyptian_date_weekday(jd);
        CHECK(weekday.find("Day") != std::string::npos);
    }

    SUBCASE("Day fortune output") {
        std::string fortune = egyptian_day_fortune(jd);
        CHECK(fortune == "Lucky" || fortune == "Unlucky" || fortune == "Very Lucky" || fortune == "Neutral");
    }
}

