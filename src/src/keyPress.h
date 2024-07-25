#pragma once
#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <Arduino.h>
#include <M5Cardputer.h>
#include "keyDefine.h"


class KeyPress
{
private:
  /* data */
public:
    int y;
    int index;
    int cursor = 0;
    bool rstOverride = false;
    bool isSwitching = true;
    int currentProc = 1;
    bool portalActive = false;
    bool pressedTvButton = false;
    bool showQrCode = false;
    bool showAPInfo = false;
    ScreenSettings dimTimer; 

    KeyPress(){
    cursor = 0;
    rstOverride = false;
    isSwitching = true;
    currentProc = 1;
    portalActive = false;
    pressedTvButton = false;
    showQrCode = false;
    showAPInfo = false;
    }

bool checkNextPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(';')) {
    cursor = cursor - 2;
    screenSetting.dimTimer();
    return true;
  }
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB) || M5Cardputer.Keyboard.isKeyPressed('.')) {
    screenSetting.dimTimer();
    return true;
  }
  return false;
}
void switcherButtonProc() {
  if (!rstOverride) {
    if (checkNextPress()) {
      isSwitching = true;
      currentProc = PROC_MAIN_MENU;
    }
  }
}

void checkPreviousPress() {
  if (M5Cardputer.Keyboard.isKeyPressed('`')) {  // Return to the main menu by pressing ESC
    dimTimer.dimTimer();

    // Reset state variables
    portalActive = false;
    pressedTvButton = false;
    showQrCode = false;
    showAPInfo = false;

    isSwitching = true;
    rstOverride = false;
    currentProc = PROC_MAIN_MENU;
  } else if (M5Cardputer.Keyboard.isKeyPressed(',')) {  // Return to the previous menu by pressing ,
    dimTimer.dimTimer();
    if (portalActive) {
      portalActive = false;
    }
    isSwitching = true;
    rstOverride = false;

    switch (currentProc) {
    case QR_CODE_MENU:
      if (showQrCode) {
        showQrCode = false;
        currentProc = QR_CODE_MENU;
      } else {
        currentProc = PROC_MAIN_MENU;
      }
      break;
    case PROC_IR_TV_MENU:
      if (pressedTvButton) {
        currentProc = PROC_IR_TV_MENU;
        pressedTvButton = false;
      } else {
        currentProc = PROC_IR_MENU;
      }
      break;
    case PROC_WIFI_BEACON:
      currentProc = PROC_WIFI_MENU;
      break;
    case PROC_WIFI_SCAN_RESULTS:
      if (showAPInfo) {
        showAPInfo = false;
        currentProc = PROC_WIFI_SCAN_RESULTS;
      } else {
        currentProc = PROC_WIFI_MENU;
      }
      break;
    case PROC_WIFI_ATTACK_MENU:
      currentProc = PROC_WIFI_MENU;
      break;
    case PROC_SIGNAL_LEVEL:
      currentProc = PROC_WIFI_ATTACK_MENU;
      break;
    case PROC_CAPTIVE_PORTAL:
      currentProc = PROC_WIFI_MENU;
      break;
    case PROC_APPLE_JUICE_MENU:
      currentProc = PROC_BLUETOOTH_MENU;
      break;
    case PROC_SWIFT_PAIR:
      currentProc = PROC_BLUETOOTH_MENU;
      break;
    case PROC_BT_MAELSTROM:
      currentProc = PROC_BLUETOOTH_MENU;
      break;
    case BATTERY_MENU:
      currentProc = PROC_SETTINGS_MENU;
      break;
    case PROC_DIMMER_MENU:
      currentProc = PROC_SETTINGS_MENU;
      break;
    case PROC_COLOR_MENU:
      currentProc = PROC_SETTINGS_MENU;
      break;
    case PROC_THEME_MENU:
      currentProc = PROC_SETTINGS_MENU;
      break;
    default:
      currentProc = PROC_MAIN_MENU;
      break;
    }
    delay(100);
  }
}



bool checkSelectPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/')) {
    screenSetting.dimTimer();
    return true;
  }
  return false;
}

bool checkESCPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed('`')) {
    screenSetting.dimTimer();
    return true;
  }
  return false;
}
void drawRoundRectMenuItems(int y, int index) {
  if (cursor == index) {
    DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
    DISPLAY.setTextColor(BG_COLOR);
  } else {
    DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
    DISPLAY.setTextColor(MAIN_COLOR);
  }
  DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
  DISPLAY.setCursor(20, y + 16);
}
};

#endif