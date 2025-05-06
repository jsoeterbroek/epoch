#pragma once
#include <Preferences.h>

#define PS_RW_MODE false
#define PS_RO_MODE true

extern Preferences psPrefs; // preferences

// Namespace
extern const char* PSNS;

extern int pspref_brightness;

void set_pspref_buzzer(bool pspref_buzzer);
bool get_pspref_buzzer();
void set_pspref_brightness(int pspref_brightness);
int get_pspref_brightness();
void incr_pspref_brightness();
void decr_pspref_brightness();

void set_pspref_calendar(int pspref_calendar);
int get_pspref_calendar();