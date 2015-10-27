#include <stdint.h>
#include <stdlib.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#include <Time.h>
#include <DS1307RTC.h>
#include <MSFTime.h>
#include <Wire.h>
#include <LiquidCrystal.h>


#define LCD_ADDR = 0x20;
#define RTC_ADDR = 0x68;


char* getRadioTime();
char* getRTCTime();
bool  setRTCTime();
char* convertToUnixEpoch(time_t t);

LiquidCrystal lcd(0);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}
