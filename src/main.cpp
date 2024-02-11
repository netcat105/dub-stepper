#include <Arduino.h>

int step_pin[4] = {2, 3, 4, 5};     // array to set outputs pin
int step_pin_val[4] = {0, 0, 0, 0}; // array to set defaults output values

int step[4][4] = {{1, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 1}, {1, 0, 0, 1}}; // 2D array that define steps progression
// STEP SEQUENCE
// 1	high	low	high	low
// 2	low	high	high	low
// 3	low	high	low	high
// 4	high	low	low	high

int last_step = 0;

// put function declarations here:

// SETUP SECTION
void setup()
{
  Serial.begin(9600);
  // init pin mode a default value with a loop
  for (int i = 0; i > 4; i++)
  {
    pinMode(step_pin[i], OUTPUT);               // set pinmode
    digitalWrite(step_pin[i], step_pin_val[i]); // digital write dafault state
  }
  Serial.println("Output port setting: Done");
}

// MAIN LOOP SECTION
void loop()
{
  // put your main code here, to run repeatedly:
}