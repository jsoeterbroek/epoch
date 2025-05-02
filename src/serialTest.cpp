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
    Serial.println(" -----------------------------------");
    delay(_delay);

    // Julian 
    Serial.println(calendar::format_julian_date_simple(jd).c_str());
    delay(_delay);

    // Gregorian
    Serial.println(calendar::format_gregorian_date_simple(jd).c_str());
    delay(_delay);

    // Islamic
    Serial.println(calendar::format_islamic_date_simple(jd).c_str());
    delay(_delay);

    // Hebrew
    Serial.println(calendar::format_hebrew_date_simple(jd).c_str());
    delay(_delay);

    // Persian 
    Serial.println(calendar::format_persian_date_simple(jd).c_str());
    delay(_delay);

    // French Rev
    Serial.println(calendar::format_french_date(jd).c_str());
    delay(_delay);



    

// French
//double jd = french_to_jd(5, 2, 10);  // Example: 10 Brumaire, Year 5
//int weekday = french_jd_to_weekday(jd);
//Serial.print("Décade weekday: ");
//Serial.println(french_weekday_name(weekday));




    Serial.println("Serial test end");
    Serial.println("+++++++++++++++++++++++++++++++++++");
    Serial.println("");
    Serial.println("");

    delay(18000);
}