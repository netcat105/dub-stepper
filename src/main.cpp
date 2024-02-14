#include <Arduino.h>
#include <MIDI.h>
#include "pitches.h"

// *---------------------------
// *Variabili relative alla riproduzione del tono tramite il motere stepper

// Integers
int last_step = 0; // ultima posizione nota dello stepper

// Arrays
int step_pin[4] = {2, 3, 4, 5};                                            // array to set outputs pin
int step_pin_val[4] = {0, 0, 0, 0};                                        // array to set defaults output values
int step[4][4] = {{1, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 1}, {1, 0, 0, 1}}; // 2D array that define steps progression
// STEP SEQUENCE
// 1	high	low	high	low
// 2	low	high	high	low
// 3	low	high	low	high
// 4	high	low	low	high

#define TIMEOUT 10000 //Number of milliseconds for watchdog timer

//The index corresponds to the MIDI channel/Motor number being used. Index 0 is not used.
unsigned long motorSpeeds[] = {0, 0, 0, 0, 0}; //holds the speeds of the motors. 
unsigned long prevStepMicros[] = {0, 0, 0, 0, 0}; //last time
const bool motorDirection = LOW; //you can use this to change the motor direction, comment out if you aren't using it.
bool disableSteppers = HIGH; //status of the enable pin. disabled when HIGH. Gets enabled when the first note on message is received.
unsigned long WDT; //Will store the time that the last event occured.

MIDI_CREATE_DEFAULT_INSTANCE(); //use default MIDI settings


// put function declarations here:

void stepRun();

// SETUP SECTION
void setup()
{
  MIDI.begin(MIDI_CHANNEL_OMNI); //listen to all MIDI channels
  MIDI.setHandleNoteOn(handleNoteOn); //execute function when note on message is recieved
  MIDI.setHandleNoteOff(handleNoteOff); //execute function when note off message is recieved
  //Serial.begin(115200); //allows for serial MIDI communication, comment out if using HIDUINO or LUFA

//!
//!   Serial.begin(9600);
//!  // * Some intial serial print messages
//!  Serial.println("*****************************************************************");
//!  Serial.println("* dub-stepper - 2024/02/12 - Max Vassalli - netcat105@gmail.com *");
//!  Serial.println("* a single stepper music player                                 *");
//!  Serial.println("* Tutti i diritti riservati.                                    *");
//!  Serial.println("*****************************************************************");
//!  Serial.println();

  // init pin mode a default value with a loop
  for (int i = 0; i < 4; i++)
  {
    pinMode(step_pin[i], OUTPUT);               // set pinmode
    digitalWrite(step_pin[i], step_pin_val[i]); // digital write dafault state
  }
  //! Serial.println("Output port setting: Done");
}

//* MAIN LOOP SECTION
void loop()
{
MIDI.read(); //read MIDI messages
  digitalWrite(enPin, disableSteppers); //choose whether to enable or disable steppers.
  singleStep(1, stepPin_M1); //run each stepper at specified speed
  singleStep(2, stepPin_M2);
  singleStep(3, stepPin_M3);
  singleStep(4, stepPin_M4);

  if (millis() - WDT >= TIMEOUT)
  {
    disableSteppers = HIGH; //When the time has elapsed, disable the steppers
  }
}

// *
// *
// * Function that order to arduino how many steps to do, and pause between each step

void handleNoteOn(byte channel, byte pitch, byte velocity) //MIDI Note ON Command
{
  disableSteppers = LOW; //enable steppers. 
  motorSpeeds[channel] = pitchVals[pitch]; //set the motor speed to specified pitch
  /*
   * something that you could potentially do is have a grid of steppers
   * and use the velocity value to determine the number of steppers in each
   * collumn should be turned on. Each collumn would have its own MIDI channel.
   * The floppotron essentially does this...
   */
}

void handleNoteOff(byte channel, byte pitch, byte velocity) //MIDI Note OFF Command
{
  motorSpeeds[channel] = 0; //set motor speed to zero
}

void singleStep(byte motorNum, byte stepPin)
{
  if ((micros() - prevStepMicros[motorNum] >= motorSpeeds[motorNum]) && (motorSpeeds[motorNum] != 0)) 
  { //step when correct time has passed and the motor is at a nonzero speed
    prevStepMicros[motorNum] += motorSpeeds[motorNum];
    WDT = millis(); //update watchdog timer
    stepRun();
  }
}


void stepRun()
{
  for (int k = 0; k <= 3; k++) // Esegue un ciclo per la scrittura delle porte d'uscita
  {
    digitalWrite(step_pin[k], step[last_step][k]); // valore di stepPin nell'array con l'indice K (0-3), e il valore della
                                                   // sequando del passo da impostare con indice dell'array 2D usando lastStep
                                                   // come primo indice la variabile laststep, e come secondo indice la variabile
                                                   // k dell'iterazione
  }
  last_step++;        // incrementa di uno l'ultimo passo eseguito
  if (last_step >= 4) // se raggiunge il valore di 4
  {                   // ... allora
    last_step = 0;    // riporta il passo a 0
  }
}