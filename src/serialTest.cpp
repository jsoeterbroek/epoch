#include <serialTest.h>
#include <Arduino.h>

int _delay = 2000;

void serialTest(void) {

    Serial.println("+++++++++++++++++++++++++++++++++++");
    Serial.println("Serial test start");
    delay(_delay);
    
    // jd_to iso
    double jd = gregorian_to_jd(2025, 5, 2);  // 5th may, 2025
    Serial.println(calendar::format_iso_date(jd).c_str());

    // TODO
    //Ancient Egypt calendar"); planetcalc 8448
    //Babylonian calendar");  https://en.wikipedia.org/wiki/Babylonian_calendar
    //Zoroastrian calendar
    //Armenian calendar  https://www.epistemeacademy.org/calendars/yearly_calendar.html?cyear=2020&vADBC=AD&CCode=Armenian&day=1  https://planetcalc.com/8491/
    //Georgian calendar https://en.wikipedia.org/wiki/Georgian_calendar
    //Mandaean calendar https://en.wikipedia.org/wiki/Mandaean_calendar
    //chinese zodiac calendar https://en.wikipedia.org/wiki/Chinese_calendar
    //buddhist https://en.wikipedia.org/wiki/Buddhist_calendar
    //Mongolian https://en.wikipedia.org/wiki/Mongolian_calendar
    //Discworld https://en.wikipedia.org/wiki/Discworld_(world)#calendar
    //Ethiopian https://en.wikipedia.org/wiki/Ethiopian_calendar  https://planetcalc.com/8504/
    //UNIX time
    //Kali Yuga
    //old norse https://en.wikipedia.org/wiki/Early_Germanic_calendars
    //shire calendar
    //360-day calendar https://en.wikipedia.org/wiki/360-day_calendar
    //Darian  https://github.com/ai/darian

    Serial.println("-----------------------------------");
    delay(_delay);

    // Julian 
    Serial.print(format_julian_date(jd).c_str());
    Serial.println(" - (Should be: 19 April 2025)");
    delay(_delay);

    // Gregorian
    Serial.print(format_gregorian_date(jd).c_str());
    Serial.println(" - (Should be: May 2, 2025)");
    delay(_delay);

    // Islamic
    Serial.println(" - (Should be: al-Jumah, 4 Dhu al-Qi'dah, 1446 AH)");
    Serial.print("format_islamic_date: ");
    Serial.println(format_islamic_date(jd).c_str());
    Serial.println("format_islamic_date_local use_arabic=false");
    Serial.println(format_islamic_date_local(jd, false).c_str());
    Serial.println("format_islamic_date_local use_arabic=true");
    Serial.println(format_islamic_date_local(jd, true).c_str());
    delay(_delay);
    Serial.println("-----------------------------------");

    // Hebrew
    Serial.print(format_hebrew_date(jd).c_str());
    Serial.println(" - (Should be: 4 Iyar, AM 5785 ----Omer 19)");
    delay(_delay);

    // Persian 
    Serial.print(format_persian_date(jd).c_str());
    Serial.println(" - (Should be: Jomeh, 12 Ordibehesht, 1404 SH)");
    delay(_delay);

    // French Rev
    Serial.println(format_french_date(jd).c_str());
    delay(_delay);

    // Mayan long
    Serial.println(format_mayan_date(jd).c_str());
    delay(_delay);

    // Mayan full
    //Serial.println(format_mayan_date_full(jd).c_str());
    //delay(_delay);

    // Saka
    Serial.println(" - (Should be: 1947 Vaisakha 12)");
    Serial.print("format_saka_date: ");
    Serial.println(format_saka_date(jd).c_str());
    Serial.print("format_saka_date_local use_hindi=false: ");
    Serial.println(format_saka_date_local(jd, false).c_str());
    Serial.print("format_saka_date_local use_hindi=true: ");
    Serial.println(format_saka_date_local(jd, true).c_str());
    delay(_delay);
    Serial.println("-----------------------------------");
    
    // Coptic
    //https://planetcalc.com/8500/
    //Serial.print(calendar::format_coptic_date(jd).c_str());
    Serial.print("Coptic: TODO");
    Serial.println(" - (Should be: Parmouti 24, 1741 AM)");
    
    // Bengali
    //Serial.print(calendar::format_bengali_date(jd).c_str());
    Serial.print("Bengali: TODO");
    Serial.println(" - (Should be: Boisakh 19, 1432 BS)");

    // Reddit 8-Day Week Calendar
    //Serial.print(calendar::format_reddit_date(jd).c_str());
    Serial.print("Reddit: TODO");
    Serial.println(" - (Should be: 26 april )");

    Serial.println("Serial test end");
    Serial.println("+++++++++++++++++++++++++++++++++++");
    Serial.println("");
    Serial.println("");

    delay(18000);
}