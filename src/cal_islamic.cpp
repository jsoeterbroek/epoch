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

/*  https://en.wikipedia.org/wiki/Islamic_calendar */

#include "calendar.h"
#include <cmath>
#include <array>
#include "astro.h"
#include <string>

//
// Islamic
//
const char* islamic_months[12] = {
    "al-Muḥarram", "Ṣafar", "Rabīʿ al-ʾAwwal", "Rabīʿ ath-Thānī", "Jumādā al-ʾŪlā", "Jumādā ath-Thāniyah",
    "Rajab", "Shaʿbān", "Ramaḍān", "Shawwāl", "Ḏū al-Qaʿdah", "Ḏū al-Ḥijjah"
};

const char* islamic_months_ar[12] = {
    "ٱلْمُحَرَّم", "صَفَر", "رَبِيع ٱلْأَوَّل", "رَبِيع ٱلثَّانِي", "جُمَادَىٰ ٱلْأُولَىٰ", "جُمَادَىٰ ٱلثَّانِيَة",
    "رَجَب", "شَعْبَان", "رَمَضَان", "شَوَّال", "ذُو ٱلْقَعْدَة", "ذُو ٱلْحِجَّة"
};

const char* islamic_weekday_names[7] = {
    "al-ʾAḥad", "al-Ithnayn", "ath-Thulāthāʾ", "al-ʾArbiʿāʾ", "al-Khamīs", "al-Jumʿah", "as-Sabt"
};

const char* islamic_weekday_names_ar[7] = {
    "ٱلْأَحَد", "الاِثْنَيْن", "ٱلثُّلَاثَاء", "ٱلْأَرْبِعَاء", "ٱلْخَمِيس", "ٱلْجُمْعَة", "ٱلسَّبْت"
};


std::array<int, 3> jd_to_islamic(double jd) {
    jd = std::floor(jd) + 0.5;
    int year = static_cast<int>(
        std::floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631.0));
    int month = static_cast<int>(
        std::min(12.0, std::ceil((jd - islamic_to_jd(year, 1, 1) + 1) / 29.5)));
    int day = static_cast<int>(jd - islamic_to_jd(year, month, 1) + 1);

    return {year, month, day};
}

double islamic_to_jd(int year, int month, int day) {
    return (day +
           std::ceil(29.5 * (month - 1)) +
           (year - 1) * 354 +
           std::floor((3 + (11 * year)) / 30.0) +
           ISLAMIC_EPOCH - 1);
}

std::string format_islamic_date(double jd) {
    auto islamic = jd_to_islamic(jd);
    int year = islamic[0], month = islamic[1], day = islamic[2];
    
    const char* name = islamic_months[month - 1];

    char buffer[40];
    snprintf(buffer, sizeof(buffer), "Islamic: %d %s, %d AH", day, name, year);
    return std::string(buffer);
}

// TODO: bidi, proper display arabic
std::string format_islamic_date_local(double jd, bool use_arabic = true) {
    auto islamic = jd_to_islamic(jd);
    int year = islamic[0], month = islamic[1], day = islamic[2];
    int weekday = calendar::iso_day_of_week(jd);  // ISO: Mon=1, Sun=7

    const char* month_name = use_arabic ? islamic_months_ar[month - 1] : islamic_months[month - 1];
    const char* weekday_name = use_arabic ? islamic_weekday_names_ar[weekday - 1] : islamic_weekday_names[weekday - 1];

    char buffer[80];
    snprintf(buffer, sizeof(buffer), "%d %s, %d (%s) :ٱلتَّقْوِيم ٱلْهِجْرِيّ", day, month_name, year, weekday_name);
    return std::string(buffer);
}