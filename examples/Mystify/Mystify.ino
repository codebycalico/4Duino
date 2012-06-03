/*
  Mystify
  Kickin' it oldschool.
  
  This sketch demonstrates the DrawPolygon method, Windows 95-style.
  
  By not redrawing the background color after each update (which is slow anyway),
  the shapes that move around the screen leave trails in their wake.
  
  This creates an effect like in the Mystify Your Mind screensaver from old
  versions of Windows (Windows Vista/7 include a newer, spiffier version
  named Mystify. This example doesn't look nearly that good ;) ).
  
  The uOLED interface isn't advanced enough to allow dimming of the screen
  to reduce the brightness of older trails, nor does it support alphatransparency.
  
  Still, pretty nice demo of how smooth animation can be.
  
  Note: You must include SoftwareSerial.h even if you're using hardware Serial*.
  These examples use SoftwareSerial, as Serial1 is unavailable on Uno,
  and Serial is unavailable (for hardware use) on Leonardo.
  You can use any serial interface you have available, though.
  Just switch out the TX/RX pins.
  
  Circuit:
  * Any Arduino should work. Tested on Uno, Mega2560, and Pro Micro (Leonardo).
  * OLED Reset on pin 8
  * RX from OLED on pin 10
  * TX to OLED on pin 9
  * OLED 5V/GND to arduino 5V/GND
  Normally it would be 8-9-10, but between the three models I tested,
  pin 10 was the only common RXable pin.

  
  This example code is in the public domain.
*/

#include "SoftwareSerial.h"
#include "FourDuino.h"
#include "OLEDUtil.h"

#define NUM_SHAPES 2 // Number of shapes
#define NUM_POINTS 4 // Number of points per shape
#define SHAPECOLOR_MAX 128 // Max RGB value for color randomization

// Should work on any device
// You can use Serial* but you still have to #include "SoftwareSerial.h"
OLED oled = OLED(8, SoftwareSerial(10,9));

// Shape colors
uint16_t color[NUM_SHAPES];
// Position of shape vertices
uint8_t pos[NUM_SHAPES][NUM_POINTS][2];
// Movement vectors for shape vertices
// Determines direction and velocity
int8_t vector[NUM_SHAPES][NUM_POINTS][2];

void setup()
{
    bool init = oled.Init();

    for (uint8_t s = 0; s < NUM_SHAPES; s++)
    {
        // Randomize the starting color of each shape
        // This is an OLED "screensaver", so let's use darker colors
        // by limiting SHAPECOLOR_MAX to a lowish value
        color[s] = Color::Random(SHAPECOLOR_MAX).To16BitRGB();

        for (uint8_t p = 0; p < NUM_POINTS; p++)
        {
            // [0] -> X
            // [1] -> Y

            // Randomize the starting pos of each vertex
            pos[s][p][0] = random(oled.GetDeviceWidth());
            pos[s][p][1] = random(oled.GetDeviceHeight());

            // Randomize the movement vector of each vertex
            // Move no more than 2 units in any direction per update
            // Don't allow zero velocity on either axis
            vector[s][p][0] = random(2) == 0 ? random(-2,0) : random(1,3); // -2,-1,1,2
            vector[s][p][1] = random(2) == 0 ? random(-2,0) : random(1,3);
        }
    }
}

void loop()
{
    // Update shapes.
    for (uint8_t s = 0; s < NUM_SHAPES; s++)
    {
        // Bounce shape vertices off the screen edges
        for (uint8_t p = 0; p < NUM_POINTS; p++)
        {
            for (uint8_t c = 0; c < 2; c++)
            {
                // Bounce when outside screen bounds
                int16_t maxDimension = (c == 0 ? oled.GetDeviceWidth() : oled.GetDeviceHeight());
                int16_t tempPos = pos[s][p][c] + vector[s][p][c];

                if (tempPos < 0 || tempPos >= maxDimension)
                // Reverse velocity
                    vector[s][p][c] = 0 - vector[s][p][c];

                // Clamp vertex coordinates to device size
                tempPos = max(0, min(maxDimension-1, tempPos));

                // Update pos
                pos[s][p][c] = tempPos;
            }
        }

        // Shift colors for each shape over time
        color[s] = Color::Blend(Color::From16BitRGB(color[s]),
            Color::Random(SHAPECOLOR_MAX), 230).To16BitRGB();
        
        // Draw the polygons
        oled.DrawPolygon(color[s], NUM_POINTS, pos[s]);
    }

    delay(10);
}
