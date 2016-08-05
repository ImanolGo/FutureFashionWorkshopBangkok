#include "CapacitiveSensor.h"


/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Modified by Becky Stern 2013 to change the color of one RGB Neo Pixel based on touch input
 */


CapacitiveSensor   cap = CapacitiveSensor(0,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
float in = 0;
int led = 1; // pulse 'digital' pin 1 - AKA the built in red LED


void setup()                    
{
   cap.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
    // initialize the digital pin as an output.
    pinMode(led, OUTPUT);
}

void loop()                    
{
    long total1 =  cap.capacitiveSensor(30);
    
   if (total1 > 4000)
    {
      float out = sin(in) * 127.5 + 127.5;
       in = in + 0.01;
       analogWrite(led, out);  // PWM the LED from 0 to 255 (max)
    }
    else 
    {
     analogWrite(led, 0);  // PWM the LED from 0 to 255 (max)
    }

    delay(10);                             // arbitrary delay to limit data to serial port 
}


