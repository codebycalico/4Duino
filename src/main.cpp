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
OLED o_led = OLED(RESET_PIN, SoftwareSerial(RX_PIN, TX_PIN));

void setup() {
    o_led.init();
    o_led.setFontOpacity(true); // Blank the area behind text
    HEIGHT = o_led.getDeviceHeight();
}

void loop(){
    
}