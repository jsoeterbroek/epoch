#include "PSpref.h"

Preferences psPrefs; // preferences

const char* PSNS = "PSPrefs";

void set_pspref_buzzer(bool _pspref_buzzer) {
    psPrefs.end();
    psPrefs.begin(PSNS, PS_RW_MODE);
    psPrefs.putBool("ps_z", _pspref_buzzer);
    psPrefs.end();
    psPrefs.begin(PSNS, PS_RO_MODE);
}

bool get_pspref_buzzer(void) {
    bool _rc = false;
    _rc = psPrefs.getBool("ps_z");
    return _rc;
}

void set_pspref_brightness(int _pspref_brightness) {
    psPrefs.end();
    psPrefs.begin(PSNS, PS_RW_MODE);
    psPrefs.putInt("ps_b", _pspref_brightness);
    psPrefs.end();
    psPrefs.begin(PSNS, PS_RO_MODE);
}

int get_pspref_brightness(void) {
    int _rc = 0;
    _rc = psPrefs.getInt("ps_b");
    if (_rc == 0) {
        set_pspref_brightness(16);
        _rc = 16;
    }
    return _rc;
}

void incr_pspref_brightness(void) {
    int _b = get_pspref_brightness();
    switch (_b) {
    case 16:
        set_pspref_brightness(32); break;
    case 32:
        set_pspref_brightness(48); break;
    case 48:
        set_pspref_brightness(64); break;
    case 64:
        set_pspref_brightness(96); break;
    case 96:
        set_pspref_brightness(132); break;
    case 132:
        set_pspref_brightness(164); break;
    case 164:
        set_pspref_brightness(180); break;
    case 180:
        set_pspref_brightness(16); break;
    default:
        set_pspref_brightness(32); break;
    }
}

void decr_pspref_brightness(void) {
    int _b = get_pspref_brightness();
    switch (_b) {
    case 16:
        set_pspref_brightness(16); break;
    case 32:
        set_pspref_brightness(16); break;
    case 48:
        set_pspref_brightness(32); break;
    case 64:
        set_pspref_brightness(48); break;
    case 96:
        set_pspref_brightness(64); break;
    case 132:
        set_pspref_brightness(96); break;
    case 164:
        set_pspref_brightness(132); break;
    case 180:
        set_pspref_brightness(164); break;
    default:
        set_pspref_brightness(61); break;
    }
}