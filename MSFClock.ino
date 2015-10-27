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


void setupLCD();
void setupRTC();

void secondsSinceRestart();
char* getRadioTime();

tmElements_t readRTC();
bool  setRTC();

char* convertToUnixEpoch(tmElements_t tm);


// Initialize LCD object with address.  
// On the LCD backpack, 0 means the default address with no jumpers set.
// This equates to 0x20 for I2C bus connections, according to the documentation.
LiquidCrystal lcd(0);


void setup() {
  Serial.begin(9600);
  setupLCD();
  delay(2000);
}

void loop() {
//  secondsSinceRestart();
  tmElements_t tm = readRTC();
  lcd.setCursor(0,1);
  lcd.print(convertToUnixEpoch(tm));
  delay(1000);  
}


/************************************************************
 * HELPERS
 ************************************************************/
void setupLCD() {
  lcd.begin(16, 2);
  lcd.print("Hello World!");
}



/************************************************************
 * WORKERS
 ************************************************************/
void secondsSinceRestart() {
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}

tmElements_t readRTC() {
  tmElements_t tm;
  lcd.setCursor(0,0);
  
  if (RTC.read(tm)) {
    lcd.print("Found RTC time!");
    return tm;
  } else {
    if (RTC.chipPresent()) {
      lcd.print("I see the RTC.");
    } else {
      lcd.print("No RTC chip.");
    }
  } 
  return tm;
}

char* convertToUnixEpoch(tmElements_t tm) {
  char timeString[16];
  sprintf(timeString, "%02d:%02d:%02d", tm.Hour, tm.Minute, tm.Second);
  Serial.println(timeString);
  return timeString;
}
