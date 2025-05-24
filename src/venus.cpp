#include "venus.h"
#include "astro.h"

namespace venus {

double phase_angle(double jd) {
    constexpr double ANCHOR = 2451623.5; // example inferior conjunction
    double days = jd - ANCHOR;
    double phase = astro::mod(days, SYNODIC_PERIOD);
    return (phase / SYNODIC_PERIOD) * 360.0;
}

int day_in_cycle(double jd) {
    constexpr double ANCHOR = 2451623.5;
    double days = jd - ANCHOR;
    return static_cast<int>(astro::mod(days, SYNODIC_PERIOD));
}

} // namespace venus
