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

//
// Darian (Mars)
//
const char* darian_months[24] = {
        "Sagittarius", "Dhanus", "Capricornus", "Makara", "Aquarius", "Kumbha",
        "Pisces", "Mina", "Aries", "Mesha", "Taurus", "Rishaba",
        "Gemini", "Mithuna", "Cancer", "Karka", "Leo", "Simha",
        "Virgo", "Kanya", "Libra", "Tula", "Scorpius", "Vrishika"
    };
    
const char* darian_weekday_names[7] = {
        "Sol Solis", "Sol Lunae", "Sol Martis", "Sol Mercurii",
        "Sol Jovis", "Sol Veneris", "Sol Saturni"
    };

// --- Convert Darian date to Julian Date ---
JD darian_to_jd(int year, int month, int sol) {
    int total_sols = 0;

    for (int y = 0; y < year; ++y) {
        total_sols += is_darian_leap_year(y) ? 669 : 668;
    }

    for (int m = 1; m < month; ++m) {
        total_sols += (m % 2 == 1) ? 28 : 27;
    }

    total_sols += (sol - 1);

    double msd = static_cast<double>(total_sols);
    return msd_to_jd(msd);
}

// --- Convert Julian Date to Darian date ---
void jd_to_darian(JD jd, int& year, int& month, int& sol) {
    int total_sols = static_cast<int>(std::floor(jd_to_msd(jd)));

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
    
// --- Format Darian date as string ---
std::string format_darian_date(int year, int month, int sol) {
 
    int total_sols = 0;
    for (int y = 0; y < year; ++y) {
        total_sols += is_darian_leap_year(y) ? 669 : 668;
    }
    for (int m = 1; m < month; ++m) {
        total_sols += (m % 2 == 1) ? 28 : 27;
    }
    total_sols += (sol - 1);
    
    int weekday_index = total_sols % 7;
    
    std::ostringstream oss;
    oss << darian_months[month - 1] << " " << sol << ", " << year << " ME ("
        << darian_weekday_names[weekday_index] << ")";
    return oss.str();
}