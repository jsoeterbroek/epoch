/* converted from */
/*
       JavaScript functions for the Fourmilab Calendar Converter

                  by John Walker  --  September, MIM
              http://www.fourmilab.ch/documents/calendar/

                This program is in the public domain.
*/

/*  You may notice that a variety of array variables logically local
    to functions are declared globally here.  In JavaScript, construction
    of an array variable from source code occurs as the code is
    interpreted.  Making these variables pseudo-globals permits us
    to avoid overhead constructing and disposing of them in each
    call on the function in which whey are used.  */

#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

namespace calendar {

// helper functions
int jd_to_weekday(double jd) {
    return static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
}

const char* day_of_week_name(int weekday) {
    static const char* names[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    return names[weekday % 7];
}

int iso_day_of_week(double jd) {
    int dow = static_cast<int>(std::fmod(std::floor(jd + 1.5), 7.0));
    return dow == 0 ? 7 : dow;  // Convert Sunday (0) to 7
}

double iso_to_jd(int year, int week, int day) {
    double jan4_jd = calendar::gregorian_to_jd(year, 1, 4);
    int jan4_dow = calendar::iso_day_of_week(jan4_jd);  // Monday = 1 ... Sunday = 7
    double week1_start = jan4_jd - (jan4_dow - 1);       // JD of Monday in ISO week 1

    return week1_start + (week - 1) * 7 + (day - 1);
}

std::array<int, 3> jd_to_iso(double jd) {
    int year = calendar::jd_to_gregorian(jd - 3)[0];

    // If this JD is in the next ISO year
    if (jd >= calendar::gregorian_to_jd(year + 1, 1, 4) - calendar::iso_day_of_week(calendar::gregorian_to_jd(year + 1, 1, 4)) + 1) {
        year++;
    }

    double jan4_jd = calendar::gregorian_to_jd(year, 1, 4);
    int jan4_dow = calendar::iso_day_of_week(jan4_jd);  // Monday=1..Sunday=7
    double week1_start = jan4_jd - (jan4_dow - 1);

    int week = static_cast<int>(std::floor((jd - week1_start) / 7.0)) + 1;

    int day = calendar::iso_day_of_week(jd);  // Monday=1..Sunday=7

    return {year, week, day};
}

std::array<int, 3> jd_to_iso_week(double jd) {
    // Start by converting JD to Gregorian
    auto gdate = calendar::jd_to_gregorian(jd);
    int year = gdate[0];

    // Find JD of the Thursday of the current ISO week
    int weekday = iso_day_of_week(jd);
    double thursday_jd = jd + (4 - weekday);

    // Get the ISO week year (may differ from Gregorian year)
    auto thursday_date = calendar::jd_to_gregorian(thursday_jd);
    int week_year = thursday_date[0];

    // JD of January 4 of the ISO week year (guaranteed to be in week 1)
    double jan4 = calendar::gregorian_to_jd(week_year, 1, 4);
    int jan4_weekday = iso_day_of_week(jan4);

    // JD of the Monday of week 1
    double week1_start = jan4 - (jan4_weekday - 1);

    // Compute ISO week number
    int week = static_cast<int>(std::floor((jd - week1_start) / 7.0) + 1);

    return {week_year, week, weekday};
}

const char* iso_weekday_name(int weekday) {
    static const char* names[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday", "Sunday"
    };
    if (weekday < 1 || weekday > 7) return "Invalid";
    return names[weekday - 1];
}

std::string format_iso_week(double jd) {
    auto date = calendar::jd_to_iso_week(jd);
    return "ISO week: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

std::string format_iso_date(double jd) {
    auto iso = jd_to_iso(jd);
    int year = iso[0];
    int week = iso[1];
    int weekday = iso[2];
    const char* name = iso_weekday_name(weekday);

    char buffer[40];
    snprintf(buffer, sizeof(buffer), "ISO: %d-W%02d-%d (%s)", year, week, weekday, name);
    return std::string(buffer);
}



//
// Gregorian
//
bool leap_gregorian(int year) {
    return ((year % 4) == 0) &&
           (!(((year % 100) == 0) && ((year % 400) != 0)));
}

bool leap_julian(int year) {
    return astro::mod(year, 4) == ((year > 0) ? 0 : 3);
}

double gregorian_to_jd(int year, int month, int day) {
    return (GREGORIAN_EPOCH - 1) +
           (365 * (year - 1)) +
           std::floor((year - 1) / 4.0) +
           -std::floor((year - 1) / 100.0) +
           std::floor((year - 1) / 400.0) +
           std::floor((((367 * month) - 362) / 12.0) +
           ((month <= 2) ? 0 :
                          (leap_gregorian(year) ? -1 : -2)) +
           day);
}

std::array<int, 3> jd_to_gregorian(double jd) {
    double wjd, depoch, quadricent, dqc, cent, dcent, quad, dquad;
    int year, month, day, yindex;
    double leapadj;

    wjd = std::floor(jd - 0.5) + 0.5;
    depoch = wjd - GREGORIAN_EPOCH;
    quadricent = std::floor(depoch / 146097.0);
    dqc = astro::mod(depoch, 146097.0);
    cent = std::floor(dqc / 36524.0);
    dcent = astro::mod(dqc, 36524.0);
    quad = std::floor(dcent / 1461.0);
    dquad = astro::mod(dcent, 1461.0);
    yindex = static_cast<int>(std::floor(dquad / 365.0));
    year = static_cast<int>(quadricent * 400 + cent * 100 + quad * 4 + yindex);
    if (!(cent == 4 || yindex == 4)) {
        year++;
    }

    int yearday = static_cast<int>(wjd - gregorian_to_jd(year, 1, 1));
    leapadj = (wjd < gregorian_to_jd(year, 3, 1)) ? 0 :
              (leap_gregorian(year) ? 1 : 2);
    month = static_cast<int>(std::floor((((yearday + leapadj) * 12) + 373) / 367.0));
    day = static_cast<int>(wjd - gregorian_to_jd(year, month, 1)) + 1;

    return {year, month, day};
}
std::string format_gregorian_date(double jd) {
    auto date = calendar::jd_to_gregorian(jd);
    return "Gregorian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

//
// Julian
//
double julian_to_jd(int year, int month, int day) {
    if (year < 1) {
        year++;
    }
    if (month <= 2) {
        year--;
        month += 12;
    }

    return std::floor(365.25 * (year + 4716)) +
           std::floor(30.6001 * (month + 1)) +
           day - 1524.5;
}

std::array<int, 3> jd_to_julian(double jd) {
    int z, a, b, c, d, e, year, month, day;

    jd += 0.5;
    z = static_cast<int>(std::floor(jd));
    a = z;
    b = a + 1524;
    c = static_cast<int>(std::floor((b - 122.1) / 365.25));
    d = static_cast<int>(std::floor(365.25 * c));
    e = static_cast<int>(std::floor((b - d) / 30.6001));

    month = (e < 14) ? (e - 1) : (e - 13);
    year = (month > 2) ? (c - 4716) : (c - 4715);
    day = static_cast<int>(b - d - std::floor(30.6001 * e));

    if (year < 1) {
        year--;
    }

    return {year, month, day};
}

std::string format_julian_date(double jd) {
    auto date = calendar::jd_to_julian(jd);
    return "Julian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

//
// Islamic
//
double islamic_to_jd(int year, int month, int day) {
    return (day +
           std::ceil(29.5 * (month - 1)) +
           (year - 1) * 354 +
           std::floor((3 + (11 * year)) / 30.0) +
           ISLAMIC_EPOCH - 1);
}

std::array<int, 3> jd_to_islamic(double jd) {
    jd = std::floor(jd) + 0.5;
    int year = static_cast<int>(
        std::floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631.0));
    int month = static_cast<int>(
        std::min(12.0, std::ceil((jd - islamic_to_jd(year, 1, 1) + 1) / 29.5)));
    int day = static_cast<int>(jd - islamic_to_jd(year, month, 1) + 1);

    return {year, month, day};
}

std::string format_islamic_date(double jd) {
    auto date = calendar::jd_to_islamic(jd);
    return "Islamic: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

//
// Hebrew
//
double hebrew_to_jd(int year, int month, int day) {
    double jd = HEBREW_EPOCH + hebrew_delay_1(year) + day + 1;

    if (month < 7) {
        for (int m = 7; m <= hebrew_year_months(year); m++) {
            jd += hebrew_month_days(year, m);
        }
        for (int m = 1; m < month; m++) {
            jd += hebrew_month_days(year, m);
        }
    } else {
        for (int m = 7; m < month; m++) {
            jd += hebrew_month_days(year, m);
        }
    }

    return jd;
}

std::array<int, 3> jd_to_hebrew(double jd) {
    jd = std::floor(jd) + 0.5;

    int count = static_cast<int>((jd - HEBREW_EPOCH) / 365.246822206);
    int year = count;

    while (jd >= hebrew_to_jd(year + 1, 7, 1)) {
        year++;
    }

    int first = (jd < hebrew_to_jd(year, 1, 1)) ? 7 : 1;
    int month = first;

    while (jd > hebrew_to_jd(year, month, hebrew_month_days(year, month))) {
        month++;
    }

    int day = static_cast<int>(jd - hebrew_to_jd(year, month, 1) + 1);
    return {year, month, day};
}

bool is_hebrew_leap(int year) {
    return (((7 * year) + 1) % 19) < 7;
}

int hebrew_year_months(int year) {
    return is_hebrew_leap(year) ? 13 : 12;
}

double hebrew_delay_1(int year) {
    double months = std::floor((235 * year - 234) / 19.0);
    double parts = 12084 + 13753 * months;
    double day = months * 29 + std::floor(parts / 25920.0);
    if ((static_cast<int>(3 * (day + 1)) % 7) < 3) {
        day++;
    }
    return day;
}

double hebrew_delay_2(int year) {
    return hebrew_delay_1(year + 1) - hebrew_year_days(year);
}

int hebrew_year_days(int year) {
    return static_cast<int>(hebrew_to_jd(year + 1, 7, 1) -
                            hebrew_to_jd(year, 7, 1));
}

int hebrew_month_days(int year, int month) {
    if (month == 2 || month == 4 || month == 6 ||
        month == 10 || month == 13) {
        return 29;
    }
    if (month == 12 && !is_hebrew_leap(year)) {
        return 29;
    }
    if (month == 8 && ((hebrew_year_days(year) % 10) != 5)) {
        return 29;
    }
    if (month == 9 && ((hebrew_year_days(year) % 10) == 3)) {
        return 29;
    }

    return 30;
}

std::string format_hebrew_date(double jd) {
    auto date = calendar::jd_to_hebrew(jd);
    return "Hebrew: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}

//
// Persian
//
double persian_to_jd(int year, int month, int day) {
    int epbase = (year >= 0) ? (year - 474) : (year - 473);
    int epyear = 474 + (epbase % 2820);

    return day +
           ((month <= 7) ? ((month - 1) * 31) : (((month - 1) * 30) + 6)) +
           std::floor((epyear * 682 - 110) / 2816.0) +
           (epyear - 1) * 365 +
           std::floor(epbase / 2820.0) * 1029983 +
           (PERSIAN_EPOCH - 1);
}

std::array<int, 3> jd_to_persian(double jd) {
    jd = std::floor(jd) + 0.5;

    double depoch = jd - persian_to_jd(475, 1, 1);
    double cycle = std::floor(depoch / 1029983.0);
    double cyear = fmod(depoch, 1029983.0);

    int ycycle;
    if (cyear == 1029982) {
        ycycle = 2820;
    } else {
        double aux1 = std::floor(cyear / 366.0);
        double aux2 = fmod(cyear, 366.0);
        ycycle = static_cast<int>(std::floor((2134.0 * aux1 + 2816.0 * aux2 + 2815.0) / 1028522.0) + aux1 + 1);
    }

    int year = ycycle + static_cast<int>(2820 * cycle) + 474;
    if (year <= 0) {
        year--;
    }

    double yday = jd - persian_to_jd(year, 1, 1) + 1;
    int month = (yday <= 186) ? static_cast<int>(std::ceil(yday / 31.0))
                              : static_cast<int>(std::ceil((yday - 6) / 30.0));
    int day = static_cast<int>(jd - persian_to_jd(year, month, 1) + 1);

    return {year, month, day};
}

std::string format_persian_date(double jd) {
    auto date = calendar::jd_to_persian(jd);
    return "Persian: " + std::to_string(date[2]) + "/" +
           std::to_string(date[1]) + "/" +
           std::to_string(date[0]);
}


//
// French (Revolutionary)
//
//This calendar:
//Was used from 1793 to 1805.
//Has 12 months of 30 days + 5 or 6 "Sansculottides".
//Each month is divided into 3 décades (10-day weeks).
//Epoch starts on 22 September 1792 (Gregorian).
//
// Leap years were defined astronomically, but Walker used a simple "every 4 years" rule for approximation (like the Julian system).
// You may want to clamp or validate month ∈ [1, 13] (13 = Sansculottides), though Walker’s code didn’t enforce it strictly.
//
//
double french_to_jd(int year, int month, int day) {
    return FRENCH_REV_EPOCH - 1 +
           365 * (year - 1) +
           std::floor((year - 1) / 4.0) +
           30 * (month - 1) +
           day;
}

std::array<int, 3> jd_to_french(double jd) {
    jd = std::floor(jd) + 0.5;
    double depoch = jd - FRENCH_REV_EPOCH;
    int year = static_cast<int>(std::floor(depoch / 365.2425)) + 1;

    while (jd >= french_to_jd(year + 1, 1, 1)) {
        year++;
    }

    int month = static_cast<int>(std::floor((jd - french_to_jd(year, 1, 1)) / 30.0)) + 1;
    int day = static_cast<int>(jd - french_to_jd(year, month, 1)) + 1;

    return {year, month, day};
}

const char* french_weekday_name(int day) {
    static const char* names[] = {
        "Primidi", "Duodi", "Tridi", "Quartidi", "Quintidi",
        "Sextidi", "Septidi", "Octidi", "Nonidi", "Décadi"
    };
    return names[day % 10];
}

int french_jd_to_weekday(double jd) {
    return static_cast<int>(std::fmod(std::floor(jd + 1.5), 10.0));
}

const char* french_month_name(int month) {
    static const char* names[] = {
        "Vendémiaire", "Brumaire", "Frimaire",      // Autumn
        "Nivôse", "Pluviôse", "Ventôse",            // Winter
        "Germinal", "Floréal", "Prairial",          // Spring
        "Messidor", "Thermidor", "Fructidor",       // Summer
        "Sansculottides"                            // Complementary days
    };

    // Clamp month to 1–13
    if (month < 1) month = 1;
    if (month > 13) month = 13;

    return names[month - 1];
}

// format functions
std::string format_french_date(double jd) {
    auto date = jd_to_french(jd);
    int year = date[0];
    int month = date[1];
    int day = date[2];

    const char* month_str = french_month_name(month);
    const char* weekday_str = french_weekday_name(french_jd_to_weekday(jd));

    return "Rev. French: " + std::string(weekday_str) + " " +
           std::to_string(day) + " " +
           month_str + ", Year " +
           std::to_string(year);
}


//
// Mayan
//
std::array<int, 5> jd_to_mayan(double jd) {
    int count = static_cast<int>(jd - MAYAN_EPOCH);

    int baktun = count / 144000;
    count %= 144000;
    int katun = count / 7200;
    count %= 7200;
    int tun = count / 360;
    count %= 360;
    int uinal = count / 20;
    int kin = count % 20;

    return {baktun, katun, tun, uinal, kin};
}
double mayan_to_jd(int baktun, int katun, int tun, int uinal, int kin) {
    return MAYAN_EPOCH +
           baktun * 144000 +
           katun * 7200 +
           tun * 360 +
           uinal * 20 +
           kin;
}

std::string format_mayan_date(double jd) {
    auto date = jd_to_mayan(jd);
    char buffer[40];
    snprintf(buffer, sizeof(buffer), "Mayan Long Count: %d.%d.%d.%d.%d",
             date[0], date[1], date[2], date[3], date[4]);
    return std::string(buffer);
}

const char* tzolkin_names[20] = {
    "Imix", "Ik’", "Ak’b’al", "K’an", "Chikchan",
    "Kimi", "Manik’", "Lamat", "Muluk", "Ok",
    "Chuwen", "Eb", "B’en", "Ix", "Men",
    "K’ib’", "Kaban", "Etz’nab’", "Kawak", "Ajaw"
};

std::pair<int, const char*> jd_to_tzolkin(double jd) {
    int day_count = static_cast<int>(jd - MAYAN_EPOCH);
    int number = ((day_count + 4) % 13) + 1;  // Ajaw was day 20, number 8 on epoch
    const char* name = tzolkin_names[(day_count + 19) % 20];
    return {number, name};
}

const char* haab_months[19] = {
    "Pop", "Wo", "Sip", "Sotz’", "Sek", "Xul",
    "Yaxk’in", "Mol", "Ch’en", "Yax", "Sak’", "Keh",
    "Mak", "K’ank’in", "Muwan", "Pax", "K’ayab", "Kumk’u", "Wayeb’"
};

std::pair<int, const char*> jd_to_haab(double jd) {
    int day_count = static_cast<int>(jd - MAYAN_EPOCH);
    int haab_day = (day_count + 348) % 365;  // 8 Kumk’u was day 0
    int day = haab_day % 20;
    int month = haab_day / 20;
    if (month == 18) day = haab_day - 360;  // Wayeb’ has only 5 days
    return {day, haab_months[month]};
}

std::string format_full_mayan_date(double jd) {
    auto lc = jd_to_mayan(jd);
    auto tz = jd_to_tzolkin(jd);
    auto haab = jd_to_haab(jd);

    char buffer[100];
    snprintf(buffer, sizeof(buffer),
             "Mayan Long Count: %d.%d.%d.%d.%d\nTzolk’in: %d %s\nHaab’: %d %s",
             lc[0], lc[1], lc[2], lc[3], lc[4],
             tz.first, tz.second,
             haab.first, haab.second);

    return std::string(buffer);
}

//
// Indian civil - saka
//
const char* saka_months[12] = {
    "Chaitra", "Vaisakha", "Jyeshtha", "Ashadha", "Shravana", "Bhadra",
    "Ashwin", "Kartika", "Agrahayana", "Pausha", "Magha", "Phalguna"
};

std::array<int, 3> jd_to_saka(double jd) {
    auto g = calendar::jd_to_gregorian(jd);
    int gy = g[0], gm = g[1], gd = g[2];

    int leap = calendar::leap_gregorian(gy) ? 1 : 0;
    int saka_year = gy - 78;
    int start_month = 3;
    int start_day = leap ? 21 : 22;

    int gday_of_year = static_cast<int>(jd - calendar::gregorian_to_jd(gy, 1, 1)) + 1;
    int saka_new_year = static_cast<int>(calendar::gregorian_to_jd(gy, start_month, start_day) -
                                         calendar::gregorian_to_jd(gy, 1, 1)) + 1;

    int saka_day_of_year;
    if (gday_of_year < saka_new_year) {
        saka_year -= 1;
        leap = calendar::leap_gregorian(gy - 1) ? 1 : 0;
        saka_day_of_year = gday_of_year + (365 + leap) - (leap ? 80 : 79);
    } else {
        saka_day_of_year = gday_of_year - saka_new_year;
    }

    int saka_month, saka_day;
    int month_lengths[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30};
    month_lengths[0] = leap ? 31 : 30;

    for (saka_month = 0; saka_month < 12; saka_month++) {
        if (saka_day_of_year < month_lengths[saka_month]) {
            saka_day = saka_day_of_year + 1;
            break;
        }
        saka_day_of_year -= month_lengths[saka_month];
    }

    return {saka_year, saka_month + 1, saka_day};
}

std::string format_saka_date(double jd) {
    auto saka = jd_to_saka(jd);
    int year = saka[0], month = saka[1], day = saka[2];

    const char* name = saka_months[month - 1];
    char buffer[40];
    snprintf(buffer, sizeof(buffer), "Saka: %d %s, %d", day, name, year);
    return std::string(buffer);
}

double saka_to_jd(int year, int month, int day) {
    int gy = year + 78;
    bool leap = calendar::leap_gregorian(gy);

    int start_day = leap ? 21 : 22;
    double jd = calendar::gregorian_to_jd(gy, 3, start_day);  // Chaitra 1

    // Month lengths
    int month_lengths[12] = {30, 31, 31, 31, 31, 31,
                             30, 30, 30, 30, 30, 30};
    month_lengths[0] = leap ? 31 : 30;  // Chaitra

    // Sum days of complete months before this one
    for (int i = 0; i < month - 1; ++i) {
        jd += month_lengths[i];
    }

    // Add day offset
    jd += day - 1;
    return jd;
}

const char* saka_months_hi[12] = {
    "चैत्र", "वैशाख", "ज्येष्ठ", "आषाढ़", "श्रावण", "भाद्रपद",
    "आश्विन", "कार्तिक", "अग्रहायण", "पौष", "माघ", "फाल्गुन"
};

const char* saka_months_sa[12] = {
    "Chaitra", "Vaishakha", "Jyeshtha", "Ashadha", "Shravana", "Bhadrapada",
    "Ashvina", "Kartika", "Agrahayana", "Pausha", "Magha", "Phalguna"
};

const char* weekday_names_hi[7] = {
    "सोमवार", "मंगलवार", "बुधवार", "गुरुवार", "शुक्रवार", "शनिवार", "रविवार"
};


const char* weekday_names_sa[7] = {
    "Somavara", "Mangalavara", "Budhavara", "Guruvara",
    "Shukravara", "Shanivara", "Ravivara"
};

std::string format_saka_date_local(double jd, bool use_hindi = true) {
    auto saka = jd_to_saka(jd);
    int year = saka[0], month = saka[1], day = saka[2];
    int weekday = calendar::iso_day_of_week(jd);  // ISO: Mon=1, Sun=7

    const char* month_name = use_hindi ? saka_months_hi[month - 1] : saka_months_sa[month - 1];
    const char* weekday_name = use_hindi ? weekday_names_hi[weekday - 1] : weekday_names_sa[weekday - 1];

    char buffer[80];
    snprintf(buffer, sizeof(buffer), "साका %d %s, %d (%s)", day, month_name, year, weekday_name);
    return std::string(buffer);
}


std::string format_all_calendars(double jd) {
    std::string result;

    result += format_gregorian_date(jd) + "\n";
    result += format_julian_date(jd) + "\n";
    result += format_iso_date(jd) + "\n";
    result += format_islamic_date(jd) + "\n";
    result += format_hebrew_date(jd) + "\n";
    result += format_persian_date(jd) + "\n";
    result += format_french_date(jd) + "\n";
    result += format_saka_date_local(jd, true) + "\n";
    result += format_full_mayan_date(jd);

    return result;
}

} // namespace calendar
