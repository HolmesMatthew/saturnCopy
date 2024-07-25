#include <Arduino.h>
#include <M5Cardputer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <EEPROM.h>
#include <WiFi.h>

#include "src/settings.h"
#include "src/language.h"
#include "src/infrared.h"
#include "src/beacon.h"
#include "src/deauth.h"
#include "src/sd.h"
#include "src/portal.h"
#include "src/applejuice.h"
#include "src/sounds.h"
#include "src/macprefixes.h"
#include "src/functions.h"
#include "src/processes.h"

/* ---------------------------------------------------------- */
#include "src/screenSettings.h"

bool screen_dim_dimmed = ScreenSettings().screen_dim_dimmed;
int screen_dim_current = ScreenSettings().screen_dim_current;
int screen_dim_time = ScreenSettings().screen_dim_time;
int brightness = ScreenSettings().brightness;

ScreenSettings screenSetting = ScreenSettings();

#include "src/keyPress.h"

KeyPress keyPress = KeyPress();

int cursor = keyPress.cursor;

bool rstOverride = keyPress.rstOverride;
bool isSwitching = keyPress.isSwitching;
int currentProc = keyPress.currentProc;
bool portalActive = keyPress.portalActive;
bool pressedTvButton = keyPress.pressedTvButton;
bool showQrCode = keyPress.showQrCode;
bool showAPInfo = keyPress.showAPInfo;







