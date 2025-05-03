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
#include "cal_gregorian.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

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

std::string format_mayan_date(double jd) {
    auto date = jd_to_mayan(jd);
    char buffer[40];
    snprintf(buffer, sizeof(buffer), "Mayan Long Count: %d.%d.%d.%d.%d",
             date[0], date[1], date[2], date[3], date[4]);
    return std::string(buffer);
}
std::string format_mayan_date_full(double jd) {
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