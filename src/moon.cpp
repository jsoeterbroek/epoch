#include "cal_gregorian.h"
#include <math.h>
#include <array>
#include "astro.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include "moon.h"

/*
https://github.com/oliverkwebb/moonphase
*/
/* Adapted from "moontool.c" by John Walker: See
 * http://www.fourmilab.ch/moontool/ */
double moonphase(double ud) {
  double eccent = 0.016718;   /* Eccentricity of Earth's orbit */
  double elonge = 278.833540; /* Ecliptic longitude of the Sun at epoch 1980.0 */
  double elongp = 282.596403; /* Ecliptic longitude of the Sun at perigee */
  double torad = M_PI / 180.0;

  /* Calculation of the Sun's position */
  double Day = (ud / 86400 + 2440587.5) - 2444238.5;                                           /* Date within epoch */
  double M = torad * fmod(fmod((((360 / 365.2422) * Day) + elonge - elongp), 360) + 360, 360); /* Convert from perigee co-ordinates to epoch 1980.0 */

  /* Solve equation of Kepler */
  double e = M, delta;
  do {
    delta = e - eccent * sin(e) - M;
    e -= delta / (1 - eccent * cos(e));
  } while (fabs(delta) > 1E-6);
  double Ec = e;
  Ec = 2 * atan(sqrt((1 + eccent) / (1 - eccent)) * tan(Ec / 2)); /* True anomaly */

  double Lambdasun = fmod(fmod((((Ec) * (180.0 / M_PI)) + elongp), 360) + 360, 360); /* Sun's geocentric ecliptic longitude */
  double ml = fmod(fmod((13.1763966 * Day + 64.975464), 360) + 360, 360);            /* Moon's mean lonigitude at the epoch */
  double MM = fmod(fmod((ml - 0.1114041 * Day - 349.383063), 360) + 360, 360);
  /* 349:  Mean longitude of the perigee at the epoch */                   /* Moon's mean anomaly */
  double Ev = 1.2739 * sin(torad * (2 * (ml - Lambdasun) - MM));           /* Evection */
  double Ae = 0.1858 * sin(M);                                             /* Annual equation */
  double MmP = torad * (MM + Ev - Ae - (0.37 * sin(M)));                   /* Corrected anomaly */
  double lP = ml + Ev + (6.2886 * sin(MmP)) - Ae + (0.214 * sin(2 * MmP)); /* Corrected longitude */
  double lPP = lP + (0.6583 * sin(torad * (2 * (lP - Lambdasun))));        /* True longitude */
  double MoonAge = lPP - Lambdasun;                                        /* Age of the Moon in degrees */

  return MoonAge * torad;
}

// Names of lunar phases
static const char *phaseNames[] = {"New", "Waxing Crescent", "First Quarter", "Waxing Gibbous", "Full", "Waning Gibbous", "Last Quarter", "Waning Crescent"};
// Names of Zodiac constellations
static const char *zodiacNames[] = {"Pisces", "Aries", "Taurus",  "Gemini",      "Cancer",    "Leo",
                                    "Virgo",  "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius"};
// Ecliptic angles of Zodiac constellations
static const float zodiacAngles[] = {33.18, 51.16, 93.44, 119.48, 135.30, 173.34, 224.17, 242.57, 271.26, 302.49, 311.72, 348.58};

int get_phase(time_t timestamp) {
  time_t target_time;

  // Use provided timestamp, or current time if 0
  if (timestamp == 0) {
    target_time = time(0);
  } else {
    target_time = timestamp;
  }

  // The moonphase function expects Unix timestamp in seconds
  double phase_radians = moonphase(static_cast<double>(target_time));

  // Convert radians to percentage properly
  // moonphase returns the moon's age in radians (0 to 2π)
  // Convert to illumination percentage: (1 - cos(phase)) / 2 * 100
  double phase_percent = (1.0 - cos(phase_radians)) / 2.0 * 100.0;

  return static_cast<int>(round(phase_percent));
}

// Overload to accept const char* for backward compatibility
int get_phase(const char *phase_arg) {
  if (phase_arg == nullptr) {
    return get_phase(static_cast<time_t>(0));
  }

  // Convert string to time_t
  time_t timestamp = static_cast<time_t>(atol(phase_arg));
  return get_phase(timestamp);
}

std::string moon_phase_name() {
  int phase = get_phase();  // Get current moon phase as percentage

  // Map percentage to phase names (0-100% illumination)
  // Based on astronomical standards:
  // The percent of the Moon's surface illuminated is a more refined, quantitative description
  // of the Moon's appearance than is the phase. Considering the Moon as a circular disk, the
  // ratio of the area illuminated by direct sunlight to its total area is the fraction of the
  // Moon's surface illuminated; multiplied by 100, it is the percent illuminated.
  // At New Moon the percent illuminated is 0; at First and Last Quarters it is 50%; and at Full
  // Moon it is 100%. During the crescent phases the percent illuminated is between 0 and 50% and
  // during gibbous phases it is between 50% and 100%.

  // Based on the example table:
  // First Quarter: 43-67% visible
  // Waxing Gibbous: 75-95% visible
  // Full Moon: 97-100% visible

  if (phase <= 1) {
    return "New";
  } else if (phase <= 25) {
    return "Waxing Crescent";
  } else if (phase <= 75) {
    return "First Quarter";
  } else if (phase <= 96) {
    return "Waxing Gibbous";
  } else if (phase <= 100) {
    return "Full";
  } else {
    // This shouldn't happen, but handle gracefully
    return "New";
  }

  // Note: This simplified version only handles waxing phases
  // A complete implementation would need to determine whether moon is waxing or waning
  // and include: "Waning Gibbous", "Last Quarter", "Waning Crescent"
}

std::string format_moon_phase() {
  return moon_phase_name();
}
