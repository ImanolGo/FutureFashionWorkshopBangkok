
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
#include "Adafruit_LSM303.h"

Adafruit_LSM303 lsm;

// mess with this number to adjust TWINklitude :)
// lower number = more sensitive
#define MOVE_THRESHOLD 500

float in = 0;
int led = 1; // pulse 'digital' pin 1 - AKA the built in red LED

void setup() 
{
  //Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
  //  Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
}

void loop() 
{
  // Take a reading of accellerometer data
  lsm.read();
  //Serial.print("Accel X: "); Serial.print(lsm.accelData.x); Serial.print(" ");
  //Serial.print("Y: "); Serial.print(lsm.accelData.y);       Serial.print(" ");
  //Serial.print("Z: "); Serial.print(lsm.accelData.z);     Serial.print(" ");

  // Get the magnitude (length) of the 3 axis vector
  // http://en.wikipedia.org/wiki/Euclidean_vector#Length
  double storedVector = lsm.accelData.x*lsm.accelData.x;
  storedVector += lsm.accelData.y*lsm.accelData.y;
  storedVector += lsm.accelData.z*lsm.accelData.z;
  storedVector = sqrt(storedVector);
  //Serial.print("Len: "); Serial.println(storedVector);
  
  // wait a bit
  delay(50);
  
  // get new data!
  lsm.read();
  double newVector = lsm.accelData.x*lsm.accelData.x;
  newVector += lsm.accelData.y*lsm.accelData.y;
  newVector += lsm.accelData.z*lsm.accelData.z;
  newVector = sqrt(newVector);
 // Serial.print("New Len: "); Serial.println(newVector);

  float mov = abs(newVector - storedVector) ;
  float col = 255.0*mov/MOVE_THRESHOLD;
   //strip.setPixelColor(0, strip.Color(col, col, col));
   //strip.show();
  // are we moving 


  float modulate = map(abs(newVector - storedVector), 0.0, MOVE_THRESHOLD, 0.0, 1.0);
  modulate = constrain(modulate, 0, 1.0); 
  
  float out = sin(in) * 127.5 + 127.5;
  in = in + 0.1 + modulate*0.9;
  out = sin(in) * 127.5 + 127.5;
 // out*=modulate;
  analogWrite(led, out);  // PWM the LED from 0 to 255 (max)
  
  if (abs(newVector - storedVector) > MOVE_THRESHOLD) {
    //Serial.println("Twinkle!");
    //analogWrite(led, 255);  // PWM the LED from 0 to 255 (max)
  }
  else{
   // analogWrite(led, 0);  // PWM the LED from 0 to 255 (max)
  }
}


