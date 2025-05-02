#include <serialTest.h>
#include <Arduino.h>

int _delay = 1000;

void serialTest(void) {


    std::array<int, 3> _date;
    Serial.println("+++++++++++++++++++++++++++++++++++");
    Serial.println("Serial test start");
    delay(_delay);
    
    // jd_to iso
    double jd = calendar::gregorian_to_jd(2025, 5, 2);  // 5th may, 2025
    Serial.println(calendar::format_iso_date(jd).c_str());
    //Serial.println("To do: Coptic calendar	Parmouti 24, 1741 AM");
    //Serial.println("To do: Solar Hijri calendar	12 Ordibehesht, 1404 SH");
    //Serial.println("To do: Bengali calendar	Boisakh 19, 1432 BS");
    //Serial.println("To do: Ancient Egypt calendar"); planetcalc 8448
    //Serial.println("To do: Babylonian calendar");
    //Zoroastrian calendar
    //Armenian calendar  https://www.epistemeacademy.org/calendars/yearly_calendar.html?cyear=2020&vADBC=AD&CCode=Armenian&day=1  https://planetcalc.com/8491/
    //Georgian calendar https://en.wikipedia.org/wiki/Georgian_calendar
    //Mandaean calendar https://en.wikipedia.org/wiki/Mandaean_calendar
    //cheines calemndar https://en.wikipedia.org/wiki/Chinese_calendar
    //buddhist https://en.wikipedia.org/wiki/Buddhist_calendar
    //Mongolian https://en.wikipedia.org/wiki/Mongolian_calendar
    //Discworld https://en.wikipedia.org/wiki/Discworld_(world)#calendar
    // Ethiopian https://en.wikipedia.org/wiki/Ethiopian_calendar  https://planetcalc.com/8504/
    // UNIX time
    // since Kali Yuga

    Serial.println("-----------------------------------");
    delay(_delay);

    // Julian 
    Serial.print(calendar::format_julian_date(jd).c_str());
    Serial.println(" - (Should be: 19 April 2025)");
    delay(_delay);

    // Gregorian
    Serial.print(calendar::format_gregorian_date(jd).c_str());
    Serial.println(" - (Should be: May 2, 2025)");
    delay(_delay);

    // Islamic
    Serial.print(calendar::format_islamic_date(jd).c_str());
    Serial.println(" - (Should be: al-Jumah, 4 Dhu al-Qi'dah, 1446 AH)");
    delay(_delay);

    // Hebrew
    Serial.print(calendar::format_hebrew_date(jd).c_str());
    Serial.println(" - (Should be: 4 Iyar, AM 5785 ----Omer 19)");
    delay(_delay);

    // Persian 
    Serial.print(calendar::format_persian_date(jd).c_str());
    Serial.println(" - (Should be: Jomeh, 12 Ordibehesht, 1404 SH)");
    delay(_delay);

    // French Rev
    Serial.println(calendar::format_french_date(jd).c_str());
    delay(_delay);

    // Mayan long
    Serial.println(calendar::format_mayan_date(jd).c_str());
    delay(_delay);

    // Mayan full
    //Serial.println(calendar::format_full_mayan_date(jd).c_str());
    //delay(_delay);

    // Saka
    Serial.print(calendar::format_saka_date(jd).c_str());
    Serial.println(" - (Should be: 1947 Vaisakha 12)");
    delay(_delay);
    
    // Coptic
    //https://planetcalc.com/8500/
    //Serial.print(calendar::format_coptic_date(jd).c_str());
    Serial.print("Coptic: TODO");
    Serial.println(" - (Should be: Parmouti 24, 1741 AM)");
    
    // Bengali
    //Serial.print(calendar::format_bengali_date(jd).c_str());
    Serial.print("Bengali: TODO");
    Serial.println(" - (Should be: Boisakh 19, 1432 BS)");


    Serial.println("Serial test end");
    Serial.println("+++++++++++++++++++++++++++++++++++");
    Serial.println("");
    Serial.println("");

    delay(18000);
}