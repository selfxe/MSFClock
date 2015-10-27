#include <stdint.h>
#include <stdlib.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#include <Time.h>
#include <DS1307RTC.h>
#include <MSFTime.h>
#include <Wire.h>


char* getRadioTime();
char* getRTCTime();
bool  setRTCTime();
char* convertToUnixEpoch(time_t t);

int LCD_ADDR = 0x20;
int RTC_ADDR = 0x68;

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
