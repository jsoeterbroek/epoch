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
// Indian civil - saka
//
const char* saka_months[12] = {
    "Chaitra", "Vaisakha", "Jyeshtha", "Ashadha", "Shravana", "Bhadra",
    "Ashwin", "Kartika", "Agrahayana", "Pausha", "Magha", "Phalguna"
};

const char* saka_months_sa[12] = {
    "Chaitra", "Vaishakha", "Jyeshtha", "Ashadha", "Shravana", "Bhadrapada",
    "Ashvina", "Kartika", "Agrahayana", "Pausha", "Magha", "Phalguna"
};

const char* saka_months_hi[12] = {
    "चैत्र", "वैशाख", "ज्येष्ठ", "आषाढ़", "श्रावण", "भाद्रपद",
    "आश्विन", "कार्तिक", "अग्रहायण", "पौष", "माघ", "फाल्गुन"
};

const char* weekday_names_sa[7] = {
    "Somavara", "Mangalavara", "Budhavara", "Guruvara",
    "Shukravara", "Shanivara", "Ravivara"
};

const char* weekday_names_hi[7] = {
    "सोमवार", "मंगलवार", "बुधवार", "गुरुवार", "शुक्रवार", "शनिवार", "रविवार"
};

std::array<int, 3> jd_to_saka(double jd) {
    auto g = jd_to_gregorian(jd);
    int gy = g[0], gm = g[1], gd = g[2];

    int leap = leap_gregorian(gy) ? 1 : 0;
    int saka_year = gy - 78;
    int start_month = 3;
    int start_day = leap ? 21 : 22;

    int gday_of_year = static_cast<int>(jd - gregorian_to_jd(gy, 1, 1)) + 1;
    int saka_new_year = static_cast<int>(gregorian_to_jd(gy, start_month, start_day) -
                                         gregorian_to_jd(gy, 1, 1)) + 1;

    int saka_day_of_year;
    if (gday_of_year < saka_new_year) {
        saka_year -= 1;
        leap = leap_gregorian(gy - 1) ? 1 : 0;
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

double saka_to_jd(int year, int month, int day) {
    int gy = year + 78;
    bool leap = leap_gregorian(gy);

    int start_day = leap ? 21 : 22;
    double jd = gregorian_to_jd(gy, 3, start_day);  // Chaitra 1

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

std::string format_saka_date(double jd) {
    auto saka = jd_to_saka(jd);
    int year = saka[0], month = saka[1], day = saka[2];

    const char* name = saka_months[month - 1];
    char buffer[40];
    snprintf(buffer, sizeof(buffer), "Saka: %d %s, %d", day, name, year);
    return std::string(buffer);
}

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