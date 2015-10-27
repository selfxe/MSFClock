#include <stdint.h>
#include <stdlib.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#include <DS1307RTC.h>
#include <Time.h>
#include <MSFTime.h>
#include <Wire.h>
#include <LiquidCrystal.h>


#define LCD_ADDR  0x20;
#define RTC_ADDR  0x68;
#define RADIO_PIN 8;


void setupLCD();
void setRTC();

void secondsSinceRestart();
void getRadioTime();
time_t msfTimeSync();

tmElements_t readRTC();

time_t convertToUnixEpoch(tmElements_t tm);


// Initialize LCD object with address.  
// On the LCD backpack, 0 means the default address with no jumpers set.
// This equates to 0x20 for I2C bus connections, according to the documentation.
LiquidCrystal lcd(0);

// Initialize the MSF radio circuit
MSFTime msf;
time_t prevDisplay = 0;
byte prevStatus = 255;



void setup() {
  Serial.begin(38400);
  setupLCD();

  msf.init(255);
  setSyncProvider(msfTimeSync);
}

void loop() {
//  secondsSinceRestart();
  getRadioTime();
  
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
  lcd.clear();
  lcd.print("UNIX Epoch Time!");
  delay(500);
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
  
  if (RTC.read(tm)) {
//    lcd.setCursor(0,0);
//    lcd.print("Found RTC time!");
    return tm;
  } else {
    if (RTC.chipPresent()) {
      lcd.setCursor(0,0);
      lcd.print("I see the RTC.");
    } else {
      lcd.setCursor(0,0);
      lcd.print("No RTC chip.");
    }
  } 
  return tm;
}

time_t convertToUnixEpoch(tmElements_t tm) {
  time_t t = makeTime(tm);
  Serial.println(t);
  return t;
}



void getRadioTime() {
  byte currStatus = msf.getStatus();
  Serial.print("Radio Status:  ");
  Serial.println(currStatus);
  if (currStatus != prevStatus || currStatus & MSF_STATUS_FIX) {
    if (currStatus != prevStatus) {
      if (currStatus & MSF_STATUS_CARRIER)
        Serial.println("Got carrier");
      if ((currStatus & MSF_STATUS_WAITING))
        Serial.println("Waiting for minute sync");
      if ((currStatus & MSF_STATUS_READING))
        Serial.println("Reading fix"); 
      prevStatus = currStatus;
    }
    
    now();

    Serial.print("value of now:  ");
    Serial.println(now());
    
    if (timeStatus()!= timeNotSet) {
      if(now() != prevDisplay) { //update the display only if the time has changed
        prevDisplay = now();
        digitalClockDisplay(); 
        RTC.set(now());
        lcd.clear();
        lcd.setCursor(0,0);
        Serial.println("Setting Time.");
        lcd.print("Setting time");
        delay(250);
        lcd.clear();
        lcd.print("UNIX Epoch Time!");
      }
    }
  }
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}


time_t msfTimeSync() {
  return msf.getTime();
}

