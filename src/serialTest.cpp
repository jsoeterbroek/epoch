#include <serialTest.h>

int _delay = 2000;

void serialTest(void) {

    //Serial.println("+++++++++++++++++++++++++++++++++++");
    Serial.println("Serial test start");
    delay(_delay);
    
    // jd_to iso
    double jd = gregorian_to_jd(2025, 5, 2);  // 2th may, 2025 (= 2460797.5)
    Serial.print("Calculated JD (should be '2460797.5'): ");
    Serial.println(jd);
    Serial.println(calendar::format_iso_date(jd).c_str());

    Serial.println("-----------------------------------");
    delay(_delay);

    // Julian 
    Serial.print(format_julian_date(jd).c_str());
    Serial.println(" - (Should be: 19 April 2025)");
    delay(_delay);
    Serial.println("-----------------------------------");

    // Gregorian
    Serial.print(format_gregorian_date(jd).c_str());
    Serial.println(" - (Should be: May 2, 2025)");
    delay(_delay);
    Serial.println("-----------------------------------");

    // Islamic
    Serial.println(" - (Should be: (al-Jumah) 4 Dhu al-Qi'dah, 1446 AH)");
    //Serial.print("format_islamic_date: ");
    ////Serial.println(format_islamic_date(jd).c_str());
    Serial.print("format_islamic_date_local: ");
    Serial.println(format_islamic_date_local(jd, false).c_str());
    //Serial.println("format_islamic_date_local use_arabic=true");
    //Serial.println(format_islamic_date_local(jd, true).c_str());
    delay(_delay);
    Serial.println("-----------------------------------");

    // Hebrew
    Serial.print(format_hebrew_date(jd).c_str());
    Serial.println(" - (Should be: 4 Iyar, AM 5785 ----Omer 19)");
    delay(_delay);
    Serial.println("-----------------------------------");

    // Persian 
    Serial.print(format_persian_date(jd).c_str());
    Serial.println(" - (Should be: Jomeh, 12 Ordibehesht, 1404 SH)");
    delay(_delay);
    Serial.println("-----------------------------------");

    // French Rev
    Serial.println(format_french_date(jd).c_str());
    delay(_delay);
    Serial.println("-----------------------------------");

    // Mayan long
    Serial.println(format_mayan_date_long(jd).c_str());
    delay(_delay);
    Serial.println("-----------------------------------");

    // Mayan local
    //Serial.println(format_mayan_date_local(jd).c_str());
    //delay(_delay);
    //Serial.println("-----------------------------------");

    // Saka
    Serial.println(" - (Should be: 12 Vaisakha 1947)");
    Serial.print("format_saka_date: ");
    Serial.println(format_saka_date(jd).c_str());
    //Serial.print("format_saka_date_local: ");
    //Serial.println(format_saka_date_local(jd, false).c_str());
    //Serial.print("format_saka_date_local use_hindi=true: ");
    //Serial.println(format_saka_date_local(jd, true).c_str());
    delay(_delay);
    Serial.println("-----------------------------------");
    
    // Coptic
    //https://planetcalc.com/8500/
    //Serial.print(format_coptic_date(jd).c_str());
    Serial.print("Coptic: TODO");
    Serial.println(" - (Should be: Parmouti 24, 1741 AM)");
    delay(_delay);
    Serial.println("-----------------------------------");
    
    // Bengali
    //Serial.print(format_bengali_date(jd).c_str());
    Serial.print("Bengali: TODO");
    Serial.println(" - (Should be: Boisakh 19, 1432 BS)");
    delay(_delay);
    Serial.println("-----------------------------------");

    // Zoroastrian
    //Serial.println(" Zoroastrian (Shenshai)");
    //Serial.println(format_zoroastrian_date(jd, ZoroastrianCalendarVariant::Shenshai));
    Serial.println(" Zoroastrian (Fasli)");
    Serial.println(format_zoroastrian_date_1(jd, ZoroastrianCalendarVariant::Fasli));
    Serial.println(format_zoroastrian_date_2(jd, ZoroastrianCalendarVariant::Fasli));
    //Serial.println(" Zoroastrian (Kadmi)");
    //Serial.println(format_zoroastrian_date(jd, ZoroastrianCalendarVariant::Kadmi));
    delay(_delay);
    Serial.println("-----------------------------------");

    Serial.println("Serial test end");
    Serial.println("+++++++++++++++++++++++++++++++++++");
    Serial.println("");
    Serial.println("");

    delay(18000);
}