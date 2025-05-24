#ifndef VENUS_H
#define VENUS_H

namespace venus {
// Synodic period of Venus in days
constexpr double SYNODIC_PERIOD = 583.92;
// Compute Venus phase angle: 0° = inferior conjunction, 180° = superior conjunction
double phase_angle(double jd);
// Day‐in‐cycle index [0..SYNODIC_PERIOD)
int day_in_cycle(double jd);
}

#endif // VENUS_H
