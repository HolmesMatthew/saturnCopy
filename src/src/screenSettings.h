#include <Arduino.h>
// Screen
bool screen_dim_dimmed = false;
int screen_dim_current = 0;
int screen_dim_time = 240;
int brightness = 100;

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