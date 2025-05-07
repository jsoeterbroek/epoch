#ifndef CAL_DARIAN_H
#define CAL_DARIAN_H

#include <string>

// --- Constants ---
constexpr double JD_EPOCH = 2405522.0028779;
constexpr double EARTH_DAYS_PER_SOL = 1.0274912517;

// --- Type aliases (optional) ---
using JD = double;

// --- Leap year check ---
inline bool is_darian_leap_year(int year);

// --- Convert Darian date to Julian Date ---
JD darian_to_jd(int year, int month, int sol);

// --- Convert Julian Date to Darian date ---
void jd_to_darian(JD jd, int& year, int& month, int& sol);

// --- Optional MSD <-> JD helpers ---
inline JD msd_to_jd(double msd) {
    return msd * EARTH_DAYS_PER_SOL + JD_EPOCH;
}

inline double jd_to_msd(JD jd) {
    return (jd - JD_EPOCH) / EARTH_DAYS_PER_SOL;
}
enum class DarianWeekStyle {
    Latin,
    Vedic
};

enum class DarianMonthStyle {
    Mythological,
    Zodiac
};

std::string darian_weekday_string(int year, int month, int sol, DarianWeekStyle style);
std::string format_darian_full_date(int year, int month, int sol, DarianWeekStyle week_style, DarianMonthStyle month_style);
std::string darian_date_string(int year, int month, int sol, DarianMonthStyle style);

#endif // CAL_DARIAN_H