/***************************************************
Developer: Joshua "SinSchism" Embrey
Date:20240502
Device: Particle Photon 2
OS: Particle.io DeviceOS 5.7.0

Description:
Demo for connecting Particle Photon 2 to the affordable
Hiletgo ILI9341 TFT display (not utilizing touchscreen)

Demo is a die roller based on some code pulled from the
Adafruit_ILI9341 graphics test app.


 ****************************************************/

// include the default adafruit headers
 #include <Adafruit_mfGFX.h>
 #include "Adafruit_ILI9341.h"
 
// define the Chip Select (CS) and Data/Command (DC) pins
 #define TFT_CS D18                                 // Standard CS connection.  Labeled as SS (Slave Select).
 #define TFT_DC D6                                  // Can be any digital pin

// declare variables
 int buttonPin = D1;
 int diceVal = 0;
 int val = 0;

// Use hardware SPI and the above for CS/DC
 Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, 0);
// If you want to use totally different pins than just the ones above, uncomment below and define other pins
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
    
  Serial.begin(9600);                               // Set serial speed and begin
  pinMode(buttonPin, INPUT_PULLUP);                 // Set the pinmode for our button to an input pullup

  tft.begin();                                      // begin the TFT functions  
  tft.setRotation(2);                               // Set rotation to have the headers at the top of the display
  
  randomSeed(analogRead(A1));                       // fetch random noise from analog input A1 to make random more... random

// Splash Screen
    tft.fillScreen(ILI9341_BLACK);                  // make Splash screen background black
    tft.setCursor(0, 0);                            // set cursor to beginning
    tft.setTextColor(ILI9341_MAGENTA);              // Use a fun color for the welcome text
    tft.setTextSize(4);                             // set text size for the main welcome
    tft.println("    Press");                       // instructions for use don't get much easier
    tft.println("   Button");                       // This is more reliable than rubbing the wires together to hotwire your die roller
    tft.println("  To Roll");                       // change this to "flip" if you do 1d2 and use it to flip a coin
    tft.println("");                                // easiest line padding
    
    tft.setTextColor(ILI9341_ORANGE);               // set text color to something different
    tft.setTextSize(10);                            // big text to declare what we're rolling
    tft.println(" 1d6");                            // this is how we roll
    
    tft.setTextSize(1);                             // small text
    tft.println("");                                // simple padding for a simple program
    tft.println("");                                // more
    tft.println("");                                // more more
    tft.setTextColor(ILI9341_WHITE);                // set a cleanly read color
    tft.println("POWERED BY PARTICLE.IO");          // Unobtrusive shilling!

}


void loop(void) {
    diceVal = 0;                                    // set the diceVal to 0 so rolls don't persist
    bool val = digitalRead(buttonPin) == LOW;       // tie the val variable to a boolean LOW
    if (val == HIGH){                               // if the button is pressed, signified by when val goes HIGH
        diceVal = random(1, 7);                     // assigns diceVal a random number between 1 and 6 (7 is the excluded upper bound)
        testText();                                 // run the testText function
        delay(100);                                 // wait 100ms to accept next request
    }
}


unsigned long testText() {
  unsigned long start = micros();                   // start the timing            
  tft.fillScreen(ILI9341_BLACK);                    // Fill the screen with black
  tft.setCursor(0, 0);                              // set the cursor to the start
  tft.setTextColor(ILI9341_WHITE);                  // set the text color to white
  tft.setTextSize(4);                               // set the text size to 4 to go across the screen cleanly
  tft.println("You Rolled ");                       // Declare what the player rolled
  if (diceVal == 1){                                // If you roll a 1...
      tft.setTextColor(ILI9341_RED);                // visualize the shame!!
  }
  else if (diceVal == 6) {                          // If you roll a 6...
      tft.setTextColor(ILI9341_YELLOW);             // Golden Glory!
  }
  else {
    tft.setTextColor(ILI9341_GREEN);                // green dice rolls
  }
  tft.setTextSize(36);                              // set dice value output to be BIG
  tft.println(diceVal);                             // put the dice value on the screen

  return micros() - start;                          // determine how long it ran
}
