/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-melody-repeat-example
   Library References: https://arduinogetstarted.com/tutorials/arduino-buzzer-library

   This example uses a piezo buzzer:
   + play a melody on background
   + repeat the melody when it is ended
   + without using delay() function, this is a non-blocking example
*/

#include <asyncBuzzer.h> // asyncBuzzer library

const int BUZZER_PIN = 3;

asyncBuzzer buzzer(BUZZER_PIN); // create asyncBuzzer object that attach to a pin;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
asyncBuzzer::Note melody[] = {
  {NOTE_E5,8}, {NOTE_E5,8}, {NOTE_E5,4},
  {NOTE_E5,8}, {NOTE_E5,8}, {NOTE_E5,4},
  {NOTE_E5,8}, {NOTE_G5,8}, {NOTE_C5,8}, {NOTE_D5,8},
  {NOTE_E5,2},
  {NOTE_F5,8}, {NOTE_F5,8}, {NOTE_F5,8}, {NOTE_F5,8},
  {NOTE_F5,8}, {NOTE_E5,8}, {NOTE_E5,8}, {NOTE_E5,16}, {NOTE_E5,16},
  {NOTE_E5,8}, {NOTE_D5,8}, {NOTE_D5,8}, {NOTE_E5,8},
  {NOTE_D5,4}, {NOTE_G5,4}
};

int noteLength;

void setup() {
  Serial.begin(9600);
  noteLength = sizeof(melody) / sizeof(melody[0]);
}

void loop() {
  buzzer.loop(); // MUST call the buzzer.loop() function in loop()

  if (buzzer.getState() == BUZZER_IDLE) { // if stopped
    buzzer.playMelody(melody, 240, noteLength); // playing
  }
}