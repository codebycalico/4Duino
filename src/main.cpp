// Calico adaptation of examples in 4Duino library

// Required for dtostrf (float-to-string conversion)
#include <stdlib.h>
#include "SoftwareSerial.h"
#include "FourDuino.h"
#include <FastLED.h>
#include <Arduino.h>
#include "OLEDUtil.h"

// Companion header to Color.h, provides a bunch of standard color literals
// Stuff like COLOR_WHITE, COLOR_PURPLE, COLOR_SLATEGRAY, COLOR_PAPAYAWHIP, etc
// Check out the file to see what is available.
#include "Colors.h"

// Avoid repeated calls to oled.getDeviceHeight() & oled.getDeviceWidth()
 uint8_t HEIGHT;
 uint8_t WIDTH;

// Current write position of the scope graph thing
// Scope loops from left to right
 uint8_t x = 0;
// Store previous analog value for drawing graph lines
uint16_t lastVal = 0;

#define RESET_PIN 8
#define TX_PIN 9
#define RX_PIN 10

// Should work on any device
// You can use Serial* but you still have to #include "SoftwareSerial.h"
// OLED(RESET_PIN, serialInterface)
OLED oled = OLED(RESET_PIN, SoftwareSerial(RX_PIN, TX_PIN));

void setup() {
    pinMode(13, OUTPUT);

    Serial.begin(9600);

    oled.init();
    oled.setFontOpacity(true); // Blank the area behind text
    HEIGHT = oled.getDeviceHeight();
    WIDTH = oled.getDeviceWidth();
}

void loop(){
// Set contrast based on photoresistor value
// Normal room light level produces about 4V
// Alternatively: oled.setContrast(OLEDUtil::scaleAnalog(analogRead(A3),15));
    oled.setContrastFromAnalog(A3);

    // Slide between background colors
    EVERY_N_MILLISECONDS( 1500 ){
        if(digitalRead(13) == HIGH){
            oled.replaceBackground(Color(255, 0, 0));
            digitalWrite(13, LOW);
        } else {
            oled.replaceBackground(Color(255, 255, 0));
            digitalWrite(13, HIGH);
        }
    }

    // Draw little face
    oled.setFill(true);
    oled.drawCircle(WIDTH/2, HEIGHT/2, HEIGHT/4, Color(0, 0, 255));
    oled.drawCircle((WIDTH/2 - 13), (HEIGHT/2 - 10), 10, Color(200, 200, 200));
    oled.drawCircle((WIDTH/2 + 13), (HEIGHT/2 - 10), 10, Color(200, 200, 200));
    //oled.drawCircle((WIDTH/2 - 15), (HEIGHT/2 - 13), 5, Color(0, 0, 0));
    //oled.drawCircle((WIDTH/2 + 15), (HEIGHT/2 - 13), 5, Color(0, 0, 0));
}