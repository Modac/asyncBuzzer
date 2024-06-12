/*
   Adapted by Modac
   Originally made for Arduino by Robson Couto
   Credit: https://github.com/robsoncouto/arduino-songs/blob/master/harrypotter/harrypotter.ino

   This example uses a piezo buzzer:
   + play Hedwig's theme from Harry Potter in the background
   + repeat the melody when it is ended
*/

#include <asyncBuzzer.h> // asyncBuzzer library

const int BUZZER_PIN = 3;

asyncBuzzer buzzer(BUZZER_PIN); // create asyncBuzzer object that attach to a pin;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
asyncBuzzer::Note melody[] = {

  // Hedwig's theme fromn the Harry Potter Movies
  // Socre from https://musescore.com/user/3811306/scores/4906610
  
  {REST, 2}, {NOTE_D4, 4},
  {NOTE_G4, -4}, {NOTE_AS4, 8}, {NOTE_A4, 4},
  {NOTE_G4, 2}, {NOTE_D5, 4},
  {NOTE_C5, -2}, 
  {NOTE_A4, -2},
  {NOTE_G4, -4}, {NOTE_AS4, 8}, {NOTE_A4, 4},
  {NOTE_F4, 2}, {NOTE_GS4, 4},
  {NOTE_D4, -1}, 
  {NOTE_D4, 4},

  {NOTE_G4, -4}, {NOTE_AS4, 8}, {NOTE_A4, 4}, //10
  {NOTE_G4, 2}, {NOTE_D5, 4},
  {NOTE_F5, 2}, {NOTE_E5, 4},
  {NOTE_DS5, 2}, {NOTE_B4, 4},
  {NOTE_DS5, -4}, {NOTE_D5, 8}, {NOTE_CS5, 4},
  {NOTE_CS4, 2}, {NOTE_B4, 4},
  {NOTE_G4, -1},
  {NOTE_AS4, 4},
     
  {NOTE_D5, 2}, {NOTE_AS4, 4},//18
  {NOTE_D5, 2}, {NOTE_AS4, 4},
  {NOTE_DS5, 2}, {NOTE_D5, 4},
  {NOTE_CS5, 2}, {NOTE_A4, 4},
  {NOTE_AS4, -4}, {NOTE_D5, 8}, {NOTE_CS5, 4},
  {NOTE_CS4, 2}, {NOTE_D4, 4},
  {NOTE_D5, -1}, 
  {REST,4}, {NOTE_AS4,4},  

  {NOTE_D5, 2}, {NOTE_AS4, 4},//26
  {NOTE_D5, 2}, {NOTE_AS4, 4},
  {NOTE_F5, 2}, {NOTE_E5, 4},
  {NOTE_DS5, 2}, {NOTE_B4, 4},
  {NOTE_DS5, -4}, {NOTE_D5, 8}, {NOTE_CS5, 4},
  {NOTE_CS4, 2}, {NOTE_AS4, 4},
  {NOTE_G4, -1}, 
  {REST, -1}, {REST, -1}
};
int tempo = 144;

int noteLength = sizeof(melody) / sizeof(melody[0]);

void setup() {
  Serial.begin(9600);
}

void loop() {
  buzzer.loop(); // MUST call the buzzer.loop() function in loop()

  if (buzzer.getState() == BUZZER_IDLE) { // if stopped
    buzzer.playMelody(melody, tempo, noteLength); // playing
  }
}