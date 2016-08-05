
#define SWITCH 0
#define LED 1

float in = 0;


void setup()                    
{
    // initialize the LED pin as an output.
  pinMode(LED, OUTPUT);
  // initialize the SWITCH pin as an input.
  pinMode(SWITCH, INPUT);
  // ...with a pullup
  digitalWrite(SWITCH, HIGH);
}

void loop()                    
{
 if (! digitalRead(SWITCH)) {  // if the button is pressed
     float out = sin(in) * 127.5 + 127.5;
     in = in + 0.001;
     analogWrite(LED, out);  // PWM the LED from 0 to 255 (max)
  } else {
    analogWrite(LED, 0);  // PWM the LED from 0 to 255 (max)
  }                            
}


