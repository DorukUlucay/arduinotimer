//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
}

int hours = 0;
int minutes = 0;
int seconds = 0;
String Time = "";
String Hour = "";
String Minute = "";
String Second = "";

void loop()
{
  seconds++;

  if (seconds % 60 == 0)
  {
    minutes++;
    seconds = 0;

    if (minutes % 60 == 0)
    {
      hours++;
      minutes = 0;
    }
  }


  lcd.clear();
  lcd.setCursor(0, 0);
  Time = FormatTime();
  lcd.print(Time);
  delay(1000);
}


String FormatTime()
{
  if  (  String(hours).length() == 1)
  {
    Hour = "0" + String(hours);
  }
  else
  {
    Hour = String(hours);
  }

  if (String(minutes).length() == 1)
  {
    Minute = "0" + String(minutes);
  }
  else
  {
    Minute = String(minutes);
  }

  if (String(seconds).length() == 1)
  {
    Second = "0" + String(seconds);
  }
  else
  {
    Second = String(seconds);
  }

  return Hour + ":" + Minute + ":" + Second;
}