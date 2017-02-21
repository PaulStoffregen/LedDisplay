/*
  HCMS Display
 Language: Arduino/Wiring

 Displays an analog value on an Avago HCMS-297x display

 String library based on the Wiring String library:
 http://wiring.org.co/learning/reference/String.html

 created 12 Jun. 2008
 modified 17 Apr 2009
 by Tom Igoe

 */
#include <LedDisplay.h>

// Define pins for the LED display.
// You can change these, just re-wire your board:
#define dataPin 6              // connects to the display's data in
#define registerSelect 7       // the display's register select pin
#define clockPin 8             // the display's clock pin
#define enable 9               // the display's chip enable pin
#define reset 10              // the display's reset pin

#define displayLength 8        // number of characters in the display

// create am instance of the LED display library:
LedDisplay myDisplay = LedDisplay(dataPin, registerSelect, clockPin,
                                  enable, reset, displayLength);

int brightness = 15;        // screen brightness

void setup() {
  // initialize the display library:
  myDisplay.begin();
  // set the brightness of the display:
  myDisplay.setBrightness(brightness);
  Serial.begin(9600);
  Serial.println(myDisplay.version(), DEC);
}

void loop() {
  // set the cursor first character
  myDisplay.home();
  myDisplay.print("A0: ");
  myDisplay.print(analogRead(0), DEC);
  myDisplay.print("   ");
}
