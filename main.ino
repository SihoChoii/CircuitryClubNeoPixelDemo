#include <Wire.h> 
#include <math.h>

// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// POT
#define PIN_POT A3
int potVal = 0;

// NEO
#include <Adafruit_NeoPixel.h>
#define PIN_NEO_PIXEL 6
#define NUM_PIXELS 60
Adafruit_NeoPixel strip(NUM_PIXELS, PIN_NEO_PIXEL, NEO_RGBW + NEO_KHZ800); // Creating strip object
int count = 0;

void setup()
{
  Serial.begin(9600);
  
  // LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  // NEO
  strip.begin();
}

void loop()
{
  // Pot Read
  potVal = analogRead(PIN_POT);
  lcd.setCursor(0,0);
  lcd.print("Pot Output: ");
  lcd.print(potVal);

  // Neo Output
  int neoOutput = potMap(potVal);
  lcd.setCursor(0,1);
  lcd.print("NEO Output: ");
  lcd.print(neoOutput);

//strip.setPixelColor(1, neoOutput, neoOutput, neoOutput, neoOutput); // Pixel # | RGBW | 0-255
  uint32_t outputColor = strip.Color(neoOutput, neoOutput, neoOutput);
  strip.fill(outputColor, 0, NUM_PIXELS);
  strip.show();

  
  
  if (abs(analogRead(PIN_POT)- potVal) > 8) lcd.clear(); // Update Threash
  delay(50);
}

int potMap(int potValue)
{
  // Pot Range
  static double potStart = 0;
  static double potEnd = 1023;
  // Analog Write Range
  static double outputStart = 0;
  static double outputEnd = 255;
  return floor((1.0 * (((outputEnd - outputStart) / (potEnd - potStart)) * (potValue - potStart))) + 0.5);
}
