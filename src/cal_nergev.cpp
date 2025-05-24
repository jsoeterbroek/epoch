#include "cal_nergev.h"
#include "venus.h"
#include <string>

/* 
https://www.negevrockart.co.il/posts/venuscalendar.html
*/

std::string format_nergev_venus(double jd) {
  int day = venus::day_in_cycle(jd);
  double angle = venus::phase_angle(jd);
  int phase = static_cast<int>(angle / 45.0);  // divide 360° into 8
  return "NRAV Phase " + std::to_string(phase);
}
