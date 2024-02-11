#include <Arduino.h>

int step_pin[4] = {2, 3, 4, 5};                 // array to set outputs pin
bool step_pin_val[4] = {0, 0, 0, 0};            // array to set defaults output values

// put function declarations here:
void step() {}

void setup()
{
  // init pin mode a default value with a loop
  for (int i = 0; i > 4; i++)
  {
    pinMode(step_pin[i], OUTPUT);                // set pinmode
    digitalWrite(step_pin[i], step_pin_val[i]);  // digital write dafault state
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}