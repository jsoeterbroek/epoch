#include "venus.h"
#include "astro.h"

/* 
Synodic periods have great historical importance, because they allowed early astronomers 
to very easily calculate approximate planet ephemeris for some years in advance. 

For example, we can consider the Venus cycle that was known to the Babylonians by the 16th 
century BC at latest. The Venus synodic period is 583.92: 5 times this is 2919.6 days.
The Earth's year is approximately 365.25 days: 8 times this is 2922.0 days. 

Thus 2922.0 days or 8 full years is approximately equal to whole numbers of years and 
synodic periods. Thus, every 2922 days or 8 years Venus is the approximately returns to the 
same position relative to the Sun and the fixed stars. Thus one can compute where Venus will 
be today, just by looking up in a table where it was 8 years ago. Or you can draw up an 
ephemeris for Venus for 8 years ahead. 

By observing Venus for 8 years, you can predict its future day by day behavior indefinitely far 
into the future with increasing error, of course. But the error can be corrected 8 years in 
advance by continually Venus observation. It is a very simple procedure. 
https://www.physics.unlv.edu/~jeffery/astro/glossary/synodic.html
 */

namespace venus {

double phase_angle(double jd) {
  constexpr double ANCHOR = 2451623.5;  // example inferior conjunction
  double days = jd - ANCHOR;
  double phase = astro::mod(days, SYNODIC_PERIOD);
  return (phase / SYNODIC_PERIOD) * 360.0;
}

int day_in_cycle(double jd) {
  constexpr double ANCHOR = 2451623.5;
  double days = jd - ANCHOR;
  return static_cast<int>(astro::mod(days, SYNODIC_PERIOD));
}

}  // namespace venus
