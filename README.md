# MSFClock
Arduino clock based on the SYM-RFT-60 radio for atomic clock time-setting using the MSF radio signal from Denver.

# Dependencies
## Hardware
 - Arduino (I'm using an Uno, rev 3.  see http://www.adafruit.com/products/50)
 - RTC chip (I'm using a DS1307 based kit, with battery backup.  see http://www.adafruit.com/products/264)
 - LCD Display (I'm using an RGB backlit 16x2 character display.  see http://www.adafruit.com/products/398)
 - I2C LCD backpack (I'm using this to simplify connections and printing.  see http://www.adafruit.com/products/292)
 - MSF Time Receiver (I'm using a WWVB 60 KHz radio kit.  see http://www.pvelectronics.co.uk/index.php?main_page=product_info&products_id=7)
 
## Software
 - Arduino IDE (v1.6.5 available from https://www.arduino.cc/en/Main/Software)
 - RTC Library (http://playground.arduino.cc/code/time)
 - LiquidCrystal library (https://github.com/adafruit/LiquidCrystal)
 - Wire library for I2C communications (http://playground.arduino.cc/Main/WireLibraryDetailedReference)
 - MSFTime library (https://github.com/jarkman/MSFTimeExample)
 
 

TIPS:
If you get an error message about duplicate definition, it's because you have included the ZIP library in your Arduino IDE AND you have the same .cpp and .h files in the folder with your .ino sketch file.  Fix this by removing the zip library (Go to ~/Documents/Arduino/libraries, and remove the folder.)
