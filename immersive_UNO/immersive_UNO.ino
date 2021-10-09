/*
  Blink a LED, Code taken from Alfa
  Turns on an LED on for one second, then off for one second, repeatedly.
  https://create.arduino.cc/projecthub/Raushancpr/1-blink-an-led-f0c1b3
  This code was taken from  codebender and published on 2016-06-15 (RGB Sensor)
  https://codebender.cc/example/Adafruit_TCS34725/tcs34725#tcs34725.ino
*/
#include <Adafruit_TCS34725.h>
#include <math.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"



/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int green_led = 13;
int yellow_led = 12;
int blue_led = 8;
int red_led = 7;

// the number of the speaker pin
 int speakerPin = 3;

int sensorValue = 0;
int outputValue = 0;

// the setup routine runs once when you press reset:
void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!

  // initialize the digital pin as an output.
  pinMode(green_led, OUTPUT);   // turn the LED on (HIGH is the voltage level)
  pinMode(yellow_led, OUTPUT);   // turn the LED on (HIGH is the voltage level)
  pinMode(blue_led, OUTPUT);   // turn the LED on (HIGH is the voltage level)
  pinMode(red_led, OUTPUT);   // turn the LED on (HIGH is the voltage level)

  pinMode(speakerPin, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop(void) {

  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  //https://stackoverflow.com/questions/26166337/find-min-value-in-array
  int nums[4] = {colorTemp - 3480, colorTemp - 3770, colorTemp - 4420, colorTemp - 6700};

  int lowestValue = nums[0];//start with lowest value
  int resultIndex = 0;
  for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); i++) {
    if ( nums[i] < 0) {
      nums[i] = nums[i] * (-1);
    }
  }
  for (int i = 1; i < sizeof(nums) / sizeof(nums[0]); i++) {
    if (nums[i] < lowestValue) {
      lowestValue = nums[i];
      resultIndex = i;
    }
  }

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  Serial.println("\n");
  Serial.println(resultIndex);
  Serial.println("\n");
  Serial.println(lowestValue);

  if (resultIndex == 0) {
    digitalWrite(yellow_led, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(speakerPin, 262 );
  }
  if (resultIndex == 1) {
    digitalWrite(red_led, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(speakerPin, 294 );
  }
  if (resultIndex == 2) {
    digitalWrite(green_led, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(speakerPin, 330 );
  }
  if (resultIndex == 3) {
    digitalWrite(blue_led, HIGH);   // turn the LED on (HIGH is the voltage level)
    tone(speakerPin, 349 );
  }
  //  digitalWrite(green_led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  digitalWrite(yellow_led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  digitalWrite(blue_led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  digitalWrite(red_led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  digitalWrite(white_led, HIGH);   // turn the LED on (HIGH is the voltage level)

  delay(1000);               // wait for a second
  digitalWrite(green_led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(yellow_led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(blue_led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(red_led, LOW);    // turn the LED off by making the voltage LOW

  noTone(speakerPin); //turn speaker off

  delay(1000);               // wait for a second



}
