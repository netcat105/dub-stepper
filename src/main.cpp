#include <Arduino.h>


int step_pin[4] = { 2,3,4,5 };

bool step_pin_val[4];




// put function declarations here:
void step() {}

void setup() {
  // put your setup code here, to run once:
for (int i = 0; i > 4; i++)
{
 pinMode(step_pin[i], OUTPUT);
 i++;
}
}

void loop() {
  // put your main code here, to run repeatedly:
}