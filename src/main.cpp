#include <Arduino.h>

// *---------------------------
// *Variabili relative alla riproduzione del tono tramite il motere stepper

// Integers
int last_step = 0;                  // ultima posizione nota dello stepper

//Arrays
int step_pin[4] = {2, 3, 4, 5};     // array to set outputs pin
int step_pin_val[4] = {0, 0, 0, 0}; // array to set defaults output values
int step[4][4] = {{1, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 1}, {1, 0, 0, 1}}; // 2D array that define steps progression
// STEP SEQUENCE
// 1	high	low	high	low
// 2	low	high	high	low
// 3	low	high	low	high
// 4	high	low	low	high


// *----------------------------
// *Varaibili reletivi al tono e alla durata
float play_tone = 0;            // nota-frequenza da riprodurre
int play_time = 0;            // durata dalla riproduzione

// put function declarations here:

void play();
// SETUP SECTION
void setup()
{
  Serial.begin(9600);
  // * Some intial serial print messages
  Serial.println("*****************************************************************");
  Serial.println("* dub-stepper - 2024/02/12 - Max Vassalli - netcat105@gmail.com *");
  Serial.println("* a single stepper music player                                 *");
  Serial.println("* Tutti i diritti riservati.                                    *");
  Serial.println("*****************************************************************");
  Serial.println();

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

void play(float *play_tone, int *play_time){
  //long play_start = micros();
  unsigned long int play_stop = micros()+long(*play_time);

  while( micros() < play_stop){
    if (last_step > 3){
      last_step = 0;
    }

    
  }

}