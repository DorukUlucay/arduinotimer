#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;
int buttonState = LOW;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long start = 0;

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(buttonPin, INPUT);
  unsigned long start = millis();
}

bool playing = false;
int hours = 0;
int minutes = 0;
int seconds = 0;
String Time = "";
String Hour = "";
String Minute = "";
String Second = "";

void loop()
{

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        playing = !playing;
      }
    }

  }
  lastButtonState = reading;






  if((millis() - start) % 1000 == 0)
  {
    if (playing)
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
    }

  }
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
