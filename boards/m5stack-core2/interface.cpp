#include <interface.h>
#include "powerSave.h"
#include <M5Unified.h>

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device
***************************************************************************************/
void _setup_gpio() {
    M5.begin(); //Need to test if SDCard inits with the new setup
}


/***************************************************************************************
** Function name: getBattery()
** location: display.cpp
** Description:   Delivers the battery value from 1-100
***************************************************************************************/
int getBattery() {
  int percent=0;
  percent = M5.Power.getBatteryLevel();
  return  (percent < 0) ? 0
        : (percent >= 100) ? 100
        :  percent;
}


/*********************************************************************
** Function: setBrightness
** location: settings.cpp
** set brightness value
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    M5.Display.setBrightness(brightval);
}

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void) {
  static long tm=millis();
  if(millis()-tm > 200 || LongPress) {
    M5.update();
    auto t = M5.Touch.getDetail();
    if (t.isPressed() || t.isHolding()) {
      tm=millis();
      if(rotation==0) {
          t.y = (tftHeight+20)-t.y;
          t.x = tftWidth-t.x;
      }
      if(rotation==1) {
          int tmp=t.x;
          t.x = tftWidth-t.y;
          t.y = tmp;
      }
      if(rotation==3) {
          int tmp=t.x;
          t.x = t.y;
          t.y = (tftHeight+20)-tmp;
      }
      if(!wakeUpScreen()) AnyKeyPress = true;
      else return;

      // Touch point global variable
      touchPoint.x = t.x;
      touchPoint.y = t.y;
      touchPoint.pressed=true;
      touchHeatMap(touchPoint);
    } else touchPoint.pressed=false;
  }
}

/*********************************************************************
** Function: powerOff
** location: mykeyboard.cpp
** Turns off the device (or try to)
**********************************************************************/
void powerOff() { }


/*********************************************************************
** Function: checkReboot
** location: mykeyboard.cpp
** Btn logic to tornoff the device (name is odd btw)
**********************************************************************/
void checkReboot() { }
