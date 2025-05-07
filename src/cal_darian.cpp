// Darian Calendar
//
//
// A Martian year in the Darian calendar has 24 months alternating between 28 and 27 sols.
//
// Non-leap years have 668 sols, leap years have 669.
// Leap years: every 10th year except every 500th year is not a leap year.
// Epoch: Darian year 0, month 1, sol 1 corresponds to MSD = 0.

// Using the Mars Sol Date (MSD) system as the intermediate.
// MSD = (JD - 2405522.0028779) / 1.0274912517

// 1 Mars year = 668.6 sols approx.
// The Darian calendar uses 24 months, alternating 28 and 27 sols, plus leap sols for intercalation.
// We’ll use the month and weekday names from the Darian calendar standard.
// Structure: 24 months per Martian year.
// Month Lengths: The first 5 months of each quarter have 28 sols (Martian days), and the 6th month has 27 sols, except in leap years when it has 28 sols.
// Leap Year Rule: A leap sol is added to the last month (Vrishika) in years where:

#include "calendar.h"
#include "cal_darian.h"
#include "astro.h"
#include <cmath>
#include <string>
#include <cmath>
#include <sstream>
#include <cstdio>

//
// Darian (Mars)
//
bool is_darian_leap_year(int year) {
    if (year % 500 == 0) return false;
    return (year % 10 == 0);
}

double darian_to_jd(int year, int month, int sol) {
    const double JD_EPOCH = 2405522.0028779;
    const double SOL_TO_EARTH_DAYS = 1.0274912517;

    int total_sols = 0;
    for (int y = 0; y < year; ++y) {
        total_sols += is_darian_leap_year(y) ? 669 : 668;
    }
    for (int m = 1; m < month; ++m) {
        total_sols += (m % 2 == 1) ? 28 : 27;
    }
    total_sols += (sol - 1);

    double msd = static_cast<double>(total_sols);
    return msd * SOL_TO_EARTH_DAYS + JD_EPOCH;
}

void jd_to_darian(double jd, int& year, int& month, int& sol) {
    const double JD_EPOCH = 2405522.0028779;
    const double SOL_TO_EARTH_DAYS = 1.0274912517;

    int total_sols = static_cast<int>((jd - JD_EPOCH) / SOL_TO_EARTH_DAYS);

    year = 0;
    while (true) {
        int sols_in_year = is_darian_leap_year(year) ? 669 : 668;
        if (total_sols < sols_in_year) break;
        total_sols -= sols_in_year;
        year++;
    }

    month = 1;
    while (true) {
        int sols_in_month = (month % 2 == 1) ? 28 : 27;
        if (total_sols < sols_in_month) break;
        total_sols -= sols_in_month;
        month++;
    }

    sol = total_sols + 1;
}

const char* darian_month_name(int month, DarianMonthStyle style) {
    static const char* mythological[24] = {
        "Aurora", "Boötes", "Caelum", "Diana", "Eurus", "Faunus",
        "Gaia", "Hercules", "Icarus", "Juno", "Kratos", "Luna",
        "Mars", "Neptune", "Ops", "Phobos", "Quirinus", "Rhea",
        "Saturn", "Terra", "Urania", "Vesta", "Wotan", "Xanthus"
    };

    static const char* zodiac[24] = {
        "Sagittarius", "Dhanus", "Capricornus", "Makara", "Aquarius", "Kumbha",
        "Pisces", "Mina", "Aries", "Mesha", "Taurus", "Rishaba",
        "Gemini", "Mithuna", "Cancer", "Karka", "Leo", "Simha",
        "Virgo", "Kanya", "Libra", "Tula", "Scorpius", "Vrishika"
    };

    if (month < 1 || month > 24) return "Invalid";
    return (style == DarianMonthStyle::Mythological) ? mythological[month - 1] : zodiac[month - 1];
}

const char* darian_weekday_name(int weekday, DarianWeekStyle style) {
    static const char* latin[7] = {
        "Sol Solis", "Sol Lunae", "Sol Martis", "Sol Mercurii",
        "Sol Jovis", "Sol Veneris", "Sol Saturni"
    };

    static const char* vedic[7] = {
        "Ravi-vāra", "Soma-vāra", "Mangala-vāra", "Budha-vāra",
        "Guru-vāra", "Shukra-vāra", "Shani-vāra"
    };

    if (weekday < 0 || weekday > 6) return "Invalid";
    return (style == DarianWeekStyle::Latin) ? latin[weekday] : vedic[weekday];
}

std::string darian_date_string(int year, int month, int sol, DarianMonthStyle style) {
    const char* month_name = darian_month_name(month, style);

    char buffer[40];
    snprintf(buffer, sizeof(buffer), "%s %d, %d ME", month_name, sol, year);
    return std::string(buffer);
}

std::string darian_weekday_string(int year, int month, int sol, DarianWeekStyle style) {
    int total_sols = 0;
    for (int y = 0; y < year; ++y) {
        total_sols += is_darian_leap_year(y) ? 669 : 668;
    }
    for (int m = 1; m < month; ++m) {
        total_sols += (m % 2 == 1) ? 28 : 27;
    }
    total_sols += (sol - 1);

    int weekday_index = total_sols % 7;
    return std::string(darian_weekday_name(weekday_index, style));
}

std::string format_darian_full_date(int year, int month, int sol, DarianWeekStyle week_style, DarianMonthStyle month_style) {
    std::string date = darian_date_string(year, month, sol, month_style);
    std::string weekday = darian_weekday_string(year, month, sol, week_style);
    return date + ", " + weekday;
}
