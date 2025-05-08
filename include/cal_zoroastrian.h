#ifndef CAL_ZOROASTRIAN_H
#define CAL_ZOROASTRIAN_H

#include <array>

enum class ZoroastrianCalendarVariant {
    Shenshai,
    Fasli,
    Kadmi
};

const char* format_zoroastrian_date_1(double jd, ZoroastrianCalendarVariant variant);
const char* format_zoroastrian_date_2(double jd, ZoroastrianCalendarVariant variant);
//const char* format_zoroastrian_date_weekday(double jd, ZoroastrianCalendarVariant variant);
//const char* format_zoroastrian_date_local(double jd, ZoroastrianCalendarVariant variant);

#endif
