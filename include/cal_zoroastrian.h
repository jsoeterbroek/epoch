#ifndef CAL_ZOROASTRIAN_H
#define CAL_ZOROASTRIAN_H

#include <array>

enum class ZoroastrianCalendarVariant {
    Shenshai,
    Fasli,
    Kadmi
};

std::array<int, 3> jd_to_zoroastrian(double jd, ZoroastrianCalendarVariant variant);
const char* format_zoroastrian_date(double jd, ZoroastrianCalendarVariant variant);

#endif
