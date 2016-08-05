
/*
  Pulse
  Pulses the internal LED to demonstrate the analogWrite function
 
  This example code is in the public domain.

  To upload to your Gemma or Trinket:
  1) Select the proper board from the Tools->Board Menu
  2) Select USBtinyISP from the Tools->Programmer
  3) Plug in the Gemma/Trinket, make sure you see the green LED lit
  4) For windows, install the USBtiny drivers
  5) Press the button on the Gemma/Trinket - verify you see
     the red LED pulse. This means it is ready to receive data
  6) Click the upload button above within 10 seconds
*/

#include <Wire.h>
#include "Adafruit_TCS34725.h"


#define MAX_LUX 50

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X);

/* Initialise with specific int time and gain values */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

float lumens = 1000;
float in = 0;
int led = 1; // pulse 'digital' pin 1 - AKA the built in red LED



void setup() 
{
   // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  tcs.begin();
  tcs.setInterrupt(true);      // turn off LED
}

void loop() 
{

  // tcs.setInterrupt(false);      // turn on LED
   uint16_t r, g, b, c, colorTemp, lux;
   tcs.getRawData(&r, &g, &b, &c);
   lumens = tcs.calculateLux(r, g, b);

  // tcs.setInterrupt(true);      // turn off LED

   float modulate = map(lumens, 0.0, MAX_LUX, 0.2, 1.0);
    modulate = constrain(modulate, 0.2, 1.0); 


  //in = in + 0.01;
  float out = sin(in) * 127.5 + 127.5;
  in = in + 0.01 + modulate*0.09;
  //out*=modulate;

  
//  if(abs(out) < 0.9){
//    uint16_t r, g, b, c, colorTemp, lux;
//    tcs.getRawData(&r, &g, &b, &c);
//    lumens = tcs.calculateLux(r, g, b);
//  }

    

  
    
  
  analogWrite(led, out);  // PWM the LED from 0 to 255 (max)
  
}


