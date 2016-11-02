#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int buttonPin = 2;
const int resetbuttonPin = 4;
int buttonState = LOW;
int resetbuttonState = LOW;
int lastButtonState = LOW;
int lastResetButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long start = 0;
bool playing = false;
int hours = 0;
int minutes = 0;
int seconds = 0;
String Time = "";
String Hour = "";
String Minute = "";
String Second = "";
String Message = "";

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(buttonPin, INPUT);
  pinMode(resetbuttonPin, INPUT);
  unsigned long start = millis();
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    Message = Serial.readString();
    delay(1);
  }

  //start-stop button
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        playing = !playing;
      }
    }
  }
  lastButtonState = reading;



  //reset the timer button
  int readingReset = digitalRead(resetbuttonPin);

  if (readingReset != lastResetButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (readingReset != resetbuttonState) {
      resetbuttonState = readingReset;

      if (resetbuttonState == HIGH) {
        Reset();
      }
    }
  }
  lastResetButtonState = readingReset;

  Tick();
}

void Reset()
{
  playing = false;
  hours = 0;
  seconds = 0;
  minutes = 0;
  PrintTime();
}

void PrintTime()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  Time = FormatTime();
  lcd.print(Time);
  lcd.setCursor(0, 1);
  lcd.print(Message);
}

void Tick()
{
  if ((millis() - start) % 1000 == 0)
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
      PrintTime();
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
