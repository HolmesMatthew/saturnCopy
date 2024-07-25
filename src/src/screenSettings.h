#pragma once
#ifndef SCREENSETTINGS_H
#define SCREENSETTINGS_H

#include <Arduino.h>
using namespace std;

class ScreenSettings {

    private:
        
    public:
        bool screen_dim_dimmed;
        int screen_dim_current;
        int screen_dim_time;
        int brightness;
        // Screen
        ScreenSettings(){
            screen_dim_dimmed = false;
            screen_dim_current = 0;
            screen_dim_time = 240;
            brightness = 100; 
        }

        void screenBrightness(int bright){
          #if defined(BACKLIGHT)
            int bl = MINBRIGHT + round(((255 - MINBRIGHT) * bright / 100)); 
            analogWrite(BACKLIGHT, bl);
          #endif
        }
        int uptime(){
          return(int(millis() / 1000));
        }
        void dimTimer(){
          if(screen_dim_dimmed){
            screenBrightness(brightness);
            screen_dim_dimmed = false;
          }
          screen_dim_current = uptime() + screen_dim_time + 2;
        }
};
#endif