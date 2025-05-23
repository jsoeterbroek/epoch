# Epoch

A calendar application for M5 Stack ePaper device.

Support for different historical and cultural calendar systems: Babylonian, Gregorian, Julian, Hebrew, Islamic, Old Egyptian, Coptic, Mayan, Persian, Republican French, Saka, Icelandic, Anglo-Saxon, Germanic, Armenian, Georgian, Mandaean, Chinese Zodiac, Buddhist, Mongolian, Ethiopian, Zoroastrian, Hindu, Mars.

## WIP
Note this project is currently very much a Work in Progress, and by no means ready. Your mileage may vary.

## Setup and configuration

* Time and date are retrieved from NTP Internet server on every (re-)start and saved to Real-Time Clock (rtc).
  Currently the NTP server address (europe.pool.ntp.org) is the default, but this needs to be user
  configurable in next release(s).
* During setup phase an Internet connection is needed in order to retrieve correct date and time via NTP.
  In order to facilitate the WiFi configuration of the device for you local WiFi network, WiFiManager is
  started during setup phase (only once), and you should be able to connect with computer and/or phone to
  SSID Network name: "m5paper" and password: "password".

  You will need to do this only once.

* The device will require an SD card inserted with all the background jpg images. These can be found in the
  data/ directory.

## Screenshots

#### All selections
![All](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/all_calendars.jpg)

### Currently implemented calendar systems

#### Babylonian
![Babylonian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/babylonian.jpg)
#### Gregorian
![Gregorian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/gregorian.jpg)
#### Julian
![Julian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/julian.jpg)
#### Islamic
![Islamic](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/islamic.jpg)
#### Old Egyptian
![Egyptian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/egyptian.jpg)
#### Mayan Long
![Mayan](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/mayan.jpg)
#### Revolutionary France
![France](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/rev_french.jpg)
#### Indian National Calendar (Saka)
![Saka](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/saka.jpg)
#### Anglo-Saxon English
![anglosaxon](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/anglosaxon.jpg)
#### Germanic (Old High German)
![germanic](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/germanic.jpg)
#### Zoroastrian
![zoroastrian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/zoroastrian.jpg)
#### Chinese (zodiac)
![chinese](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/chin_zodiac.jpg)
#### Mars (Darian)
![Mars](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/mars.jpg)
#### Hebrew
![Hebrew](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/hebrew.jpg)
#### Coptic
![Coptic](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/coptic.jpg)
#### Icelandic
![icelandic](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/icelandic.jpg)
#### Buddhist (Thai Solar)
![buddhist](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/buddhist_thai.jpg)
#### Hindu
![hindu](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/hindu.jpg)
#### Ethiopian
![ethiopoian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/ethiopian.jpg)

### To be implemented calendar systems

#### Persian
![Persian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/persian.jpg)
#### Armenian
![armenian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/armenian.jpg)
#### Georgian
![georgian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/georgian.jpg)
#### Mandaean
![mandaean](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/mandaean.jpg)
#### Mongolian
![Mongolian](https://github.com/jsoeterbroek/epoch/blob/main/assets/screens/mongolian.jpg)

## TODO
* remaining calendar systems
* bidi support (if possible)
* unicode support (if possible)
* more localization languages
* configuration option to select your default calendar (now Gregorian) (Issue #1)
* configuration option to manually change time, date (now set by NTP) (Issue #2)
* configuration option to change timezone (Europe/Amsterdam now default) (Issue #3)

## Help needed
If you want to help to further develop Epoch, your help is very welcome. Check the TODO items in this README.

I would especially welcome help or assistance if you would test the relevant calendar for your
cultural or religious background, if the calculations, localisations etc. are correct or we are missing something.

I try to test as best I can with all kinds of calendar conversion apps or websites, but this is very complicated
in practice.

## License
See file LICENSE

## Aknowledgements
See file Aknowledgements
