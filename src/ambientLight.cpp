// /*
//   Ambient Light sensing + auto-contrast adjust
//   by Ash Wolford (planetarian)
//   Because OLEDs are bright, yo.

//   This sketch demonstrates using a photoresistor to detect light and adjust
//   the screen contrast based on the light level.

//   It also draws an oscilloscope-like view of the voltage level coming into the
//   photoresistor pin, demonstrating line-drawing and text readouts.

//   The photoresistor circuit acts as a voltage divider (in combination with the 10k
//   GND connection), and the OLED library can take an analog pin as input and
//   automatically set the brightness level accordingly.

//   If you don't have a photoresistor handy, you can provide it an unconnected
//   analog pin (perhaps with a dead-end wire acting as an antenna) and let the
//   floating voltage do what it may =)
  
//   Note that the line is not antialiased -- The GOLDELOX controller doesn't
//   seem to be capable of complex operations like edge smoothing, so everything's
//   all jaggy. Large screen updates also take a great deal of time, so you probably
//   won't be playing DOOM on this thing any time soon =)
  
//   Circuit:
//   * Any Arduino should work. Tested on Uno, Mega2560, and Pro Micro (Leonardo).
//   * D8 -> OLED Reset
//   * D10 -> OLED TX
//   * D9 -> 1kOhm resistor -> OLED RX
//   * OLED 5V/GND to arduino 5V/GND
//   * 5V -> Photoresistor -> A3 -> 10kOhm resistor -> GND
//   Note that you can change this to use whatever pins you want for the serial connection,
//   but only certain pins can be used as SoftwareSerial RX.
//   In the three models I tested, pin 10 was the only common RXable pin.

  
//   Note: You must include SoftwareSerial.h even if you're using hardware Serial*.
//   These examples use SoftwareSerial, as Serial1 is unavailable on Uno,
//   and Serial is unavailable (for hardware use) on Leonardo.
//   You can use any serial interface you have available, though.
//   Just switch out the TX/RX pins.

//   This example code is in the public domain.
// */


// // Required for dtostrf (float-to-string conversion)
// #include <stdlib.h>

// #include "SoftwareSerial.h"
// #include "FourDuino.h"

// // Companion header to Color.h, provides a bunch of standard color literals
// // Stuff like COLOR_WHITE, COLOR_PURPLE, COLOR_SLATEGRAY, COLOR_PAPAYAWHIP, etc
// // Check out the file to see what is available.
// #include "Colors.h"

// // Avoid repeated calls to oled.getDeviceHeight()
// uint8_t HEIGHT;
// // Current write position of the scope graph thing
// // Scope loops from left to right
// uint8_t x = 0;
// // Store previous analog value for drawing graph lines
// uint16_t lastVal = 0;

// // OLED(pinReset, serialInterface);

// #define RESET_PIN 8
// #define TX_PIN 9
// #define RX_PIN 10

// // Should work on any device
// // You can use Serial* but you still have to #include "SoftwareSerial.h"
// // OLED(RESET_PIN, serialInterface)
// OLED o_led = OLED(RESET_PIN, SoftwareSerial(RX_PIN, TX_PIN));

// void setup()
// {
//     o_led.init();
//     o_led.setFontOpacity(true); // Blank the area behind text
//     HEIGHT = o_led.getDeviceHeight();
// }


// void loop()
// {
//     // Set contrast based on photoresistor value
//     // Normal room light level produces about 4V
//     // Alternatively: oled.setContrast(OLEDUtil::scaleAnalog(analogRead(A3),15));
//     o_led.setContrastFromAnalog(A3);
    


//     // Clear columns for new oscilloscope data
//     // drawLine(x1, y1, x2, y2, color)
//     // draw functions can accept colors as 16-bit color values or Color objects
//     o_led.drawLine(x, 0, x, HEIGHT-1, Color(0,30,0));
//     o_led.drawLine(x+1, 0, x+1, HEIGHT-1, Color(20,60,20)); // lighter color for the 'write head'

//     // +5V -> Photoresistor -> A3 -> 10kOhm -> GND
//     uint16_t newVal = analogRead(A3);
//     // Draw a line from the previous reading to the current one
//     o_led.drawLine(
//         x, HEIGHT - 1 - OLEDUtil::scaleAnalog(lastVal, HEIGHT),
//         x+1, HEIGHT - 1 - OLEDUtil::scaleAnalog(newVal, HEIGHT),
//         COLOR_LIME);
    


//     // Convert the analog reading (0-1023) to the Contrast scale (0-15)
//     uint16_t contrast = OLEDUtil::scaleAnalog(newVal, 15);
//     // Report the new contrast value
//     // drawText(column, row, text)
//     o_led.drawText(0, 6, (String)"C:" + contrast + " ");

//     // Report the actual voltage level of the analog input.
//     // dtostrf() takes a float value and converts it to a string.
//     // str must be initialized prior to calling the function to prevent weird memory stuff.
//     // dtostrf(float Value, total string width (without null byte), precision, decimal places)
//     char str[5] = "0.00";
//     o_led.drawText(0, 7, (String)"A3:" + dtostrf(OLEDUtil::analogToVoltage(newVal), 4, 2, str) + "v");
    


//     // Save the value for the next loop
//     lastVal = newVal;

//     // Jump back to the left side once the scope reaches the right edge
//     x+=1;
//     if (x >= o_led.getDeviceWidth())
//         x = 0;



//     // The screen takes long enough to draw updates that a delay isn't really even necessary.
//     //delay(1000/60);
// }