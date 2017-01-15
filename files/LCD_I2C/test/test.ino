/*
下載函式庫:https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address



void setup() 
{
  Serial.begin(9600);  // Used to type in characters

  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines and turn on backlight

  for(int i = 0; i< 3; i++) //背光閃爍三次
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
  

  lcd.setCursor(0,0); 
  lcd.print("Hello, world!");
  delay(1000);
  
  lcd.setCursor(0,1);
  lcd.print("Row2");
  delay(1000);  
  
  lcd.setCursor(0,2);
  lcd.print("Row3");
  delay(1000);
  
  lcd.setCursor(0,3);
  lcd.print("Row4");
  delay(1000);


}


void loop()   
{
  {
    // when characters arrive over the serial port...
    if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      lcd.clear();
      // read all the available characters
      while (Serial.available() > 0) {
        // display each character to the LCD
        lcd.write(Serial.read());
      }
    }
  }

}
