#ifndef CAL_ZOROASTRIAN_H
#define CAL_ZOROASTRIAN_H

#include <array>

enum class ZoroastrianCalendarVariant {
  Shenshai,
  Fasli,
  Kadmi
};

std::array<int, 3> jd_to_zoroastrian(double jd, ZoroastrianCalendarVariant variant);

const char *format_zoroastrian_date_roj(double jd, ZoroastrianCalendarVariant variant);  // 'weekday'
const char *format_zoroastrian_date_mah(double jd, ZoroastrianCalendarVariant variant);  // 'month'

#endif
