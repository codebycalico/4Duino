// Calico adaptation of examples in 4Duino library

// Required for dtostrf (float-to-string conversion)
#include <stdlib.h>

#include "SoftwareSerial.h"
#include "FourDuino.h"

// Companion header to Color.h, provides a bunch of standard color literals
// Stuff like COLOR_WHITE, COLOR_PURPLE, COLOR_SLATEGRAY, COLOR_PAPAYAWHIP, etc
// Check out the file to see what is available.
#include "Colors.h"

// Avoid repeated calls to oled.getDeviceHeight()
uint8_t HEIGHT;
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
    oled.init();
    oled.setFontOpacity(true); // Blank the area behind text
    HEIGHT = oled.getDeviceHeight();
    oled.setBackground(Color(0, 200, 0));
}

void loop(){
    //oled.replaceBackground(Color(255, 0, 0));
    // // Set contrast based on photoresistor value
    // // Normal room light level produces about 4V
    // // Alternatively: oled.setContrast(OLEDUtil::scaleAnalog(analogRead(A3),15));
    // oled.setContrastFromAnalog(A3);

    // // Clear columns for new oscilloscope data
    // // drawLine(x1, y1, x2, y2, color)
    // // draw functions can accept colors as 16-bit color values or Color objects
    // oled.drawLine(x, 0, x, HEIGHT-1, Color(0,30,0));
    // oled.drawLine(x+1, 0, x+1, HEIGHT-1, Color(20,60,20)); // lighter color for the 'write head'
    
    // // +5V -> Photoresistor -> A3 -> 10kOhm -> GND
    // uint16_t newVal = analogRead(A3);
    // // Draw a line from the previous reading to the current one
    // oled.drawLine(
    //     x, HEIGHT - 1 - OLEDUtil::scaleAnalog(lastVal, HEIGHT),
    //     x+1, HEIGHT - 1 - OLEDUtil::scaleAnalog(newVal, HEIGHT),
    //     COLOR_LIME
    // );

}