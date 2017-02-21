/*
  HCMS Display
 Language: Arduino/Wiring

 Displays a string on an Avago HCMS-297x display
 Scrolls the current display string as well.
 Anything you send in the serial port is displayed
 when the Arduino receives a newline or carriage return.

 String library based on the Wiring String library:
 http://wiring.org.co/learning/reference/String.html

 created 12 Jun. 2008
 modified 11 March 2010
 by Tom Igoe

 */
#include <WString.h>
#include <LedDisplay.h>

#define maxStringLength 180  // max string length

// Define pins for the LED display.
// You can change these, just re-wire your board:
#define dataPin 6              // connects to the display's data in
#define registerSelect 7       // the display's register select pin
#define clockPin 8             // the display's clock pin
#define enable 9               // the display's chip enable pin
#define reset 10               // the display's reset pin

#define displayLength 8        // number of chars in the display

// create am instance of the LED display:
LedDisplay myDisplay = LedDisplay(dataPin, registerSelect, clockPin,
                                  enable, reset, displayLength);

int brightness = 15;        // screen brightness

String displayString;        // the string currently being displayed
String bufferString;         // the buffer for receiving incoming characters

void setup() {
  Serial.begin(9600);
  // set an initial string to display:
  displayString = "Use the Arduino Serial Monitor to send a new string.";

  // initialize the display library:
  myDisplay.begin();
  // set the display string, speed,and brightness:
  myDisplay.setString(displayString.c_str());
  myDisplay.setBrightness(brightness);
}

void loop() {
  // get new data in from the serial port:
  while (Serial.available() > 0) {
    // read in new serial:
    getSerial();
  }

  // srcoll left and right:
  /*if ((myDisplay.getCursor() >= 0) ||
    (myDisplay.getCursor() <= -(myDisplay.stringLength() - 8))) {
    myDirection = -myDirection;
    delay(1000);
  }
*/
  if (myDisplay.getCursor() <= -(myDisplay.stringLength() - 8)) {
    // when the string reaches the end, stop and then fade out
    delay(500);
    for (int n=brightness; n >= 0; n--) {
      myDisplay.setBrightness(n);
      delay(50);
    }
    // start the string back from the beginning
    myDisplay.setCursor(0);
    myDisplay.scroll(0);
    // fade back in
    for (int n=1; n <= brightness; n++) {
      myDisplay.setBrightness(n);
      delay(25);
    }
    delay(500);
    return;
  }
  myDisplay.scroll(-1); // direction of scrolling. -1 = left, 1 = right.
  delay(100);

}

void getSerial() {
  // get a new byte in the serial port:
  int inByte = Serial.read();
  switch (inByte) {
  case '\n':
  case '\r':
    // if you get a newline,
    // copy the buffer into the displayString:
    displayString = bufferString;
    // set the display with the new string:
    myDisplay.setString(displayString.c_str());
    // set the cursor, so the old string fade away now
    myDisplay.setCursor(-1000);
    // clear the buffer:
    bufferString = "";
    break;
  default:
    // if you get any ASCII alphanumeric value
    // (i.e. anything greater than a space), add it to the buffer:
    if (inByte >= ' ') {
      if (bufferString.length() < maxStringLength) {
        bufferString.concat(char(inByte));
      }
    }
    break;
  }
}
