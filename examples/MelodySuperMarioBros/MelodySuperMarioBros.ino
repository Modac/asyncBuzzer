/*
   Adapted by Modac
   Originally made for Arduino by Robson Couto
   Credit: https://github.com/robsoncouto/arduino-songs/blob/master/supermariobros/supermariobros.ino
   Tipp: To convert the format from these sketches in Notepad++ search for: "(?<1>[A-Z_]+\d?,-?\d)" and replace with "{\1}"

   This example uses a piezo buzzer:
   + play Overworld Theme from Super Mario Bros in the background
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

  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  
  {NOTE_E5,8}, {NOTE_E5,8}, {REST,8}, {NOTE_E5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_E5,8}, //1
  {NOTE_G5,4}, {REST,4}, {NOTE_G4,8}, {REST,4}, 
  {NOTE_C5,-4}, {NOTE_G4,8}, {REST,4}, {NOTE_E4,-4}, // 3
  {NOTE_A4,4}, {NOTE_B4,4}, {NOTE_AS4,8}, {NOTE_A4,4},
  {NOTE_G4,-8}, {NOTE_E5,-8}, {NOTE_G5,-8}, {NOTE_A5,4}, {NOTE_F5,8}, {NOTE_G5,8},
  {REST,8}, {NOTE_E5,4},{NOTE_C5,8}, {NOTE_D5,8}, {NOTE_B4,-4},
  {NOTE_C5,-4}, {NOTE_G4,8}, {REST,4}, {NOTE_E4,-4}, // repeats from 3
  {NOTE_A4,4}, {NOTE_B4,4}, {NOTE_AS4,8}, {NOTE_A4,4},
  {NOTE_G4,-8}, {NOTE_E5,-8}, {NOTE_G5,-8}, {NOTE_A5,4}, {NOTE_F5,8}, {NOTE_G5,8},
  {REST,8}, {NOTE_E5,4},{NOTE_C5,8}, {NOTE_D5,8}, {NOTE_B4,-4},

  
  {REST,4}, {NOTE_G5,8}, {NOTE_FS5,8}, {NOTE_F5,8}, {NOTE_DS5,4}, {NOTE_E5,8},//7
  {REST,8}, {NOTE_GS4,8}, {NOTE_A4,8}, {NOTE_C4,8}, {REST,8}, {NOTE_A4,8}, {NOTE_C5,8}, {NOTE_D5,8},
  {REST,4}, {NOTE_DS5,4}, {REST,8}, {NOTE_D5,-4},
  {NOTE_C5,2}, {REST,2},

  {REST,4}, {NOTE_G5,8}, {NOTE_FS5,8}, {NOTE_F5,8}, {NOTE_DS5,4}, {NOTE_E5,8},//repeats from 7
  {REST,8}, {NOTE_GS4,8}, {NOTE_A4,8}, {NOTE_C4,8}, {REST,8}, {NOTE_A4,8}, {NOTE_C5,8}, {NOTE_D5,8},
  {REST,4}, {NOTE_DS5,4}, {REST,8}, {NOTE_D5,-4},
  {NOTE_C5,2}, {REST,2},

  {NOTE_C5,8}, {NOTE_C5,4}, {NOTE_C5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_D5,4},//11
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_A4,8}, {NOTE_G4,2},

  {NOTE_C5,8}, {NOTE_C5,4}, {NOTE_C5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_D5,8}, {NOTE_E5,8},//13
  {REST,1}, 
  {NOTE_C5,8}, {NOTE_C5,4}, {NOTE_C5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_D5,4},
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_A4,8}, {NOTE_G4,2},
  {NOTE_E5,8}, {NOTE_E5,8}, {REST,8}, {NOTE_E5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_E5,4},
  {NOTE_G5,4}, {REST,4}, {NOTE_G4,4}, {REST,4}, 
  {NOTE_C5,-4}, {NOTE_G4,8}, {REST,4}, {NOTE_E4,-4}, // 19
  
  {NOTE_A4,4}, {NOTE_B4,4}, {NOTE_AS4,8}, {NOTE_A4,4},
  {NOTE_G4,-8}, {NOTE_E5,-8}, {NOTE_G5,-8}, {NOTE_A5,4}, {NOTE_F5,8}, {NOTE_G5,8},
  {REST,8}, {NOTE_E5,4}, {NOTE_C5,8}, {NOTE_D5,8}, {NOTE_B4,-4},

  {NOTE_C5,-4}, {NOTE_G4,8}, {REST,4}, {NOTE_E4,-4}, // repeats from 19
  {NOTE_A4,4}, {NOTE_B4,4}, {NOTE_AS4,8}, {NOTE_A4,4},
  {NOTE_G4,-8}, {NOTE_E5,-8}, {NOTE_G5,-8}, {NOTE_A5,4}, {NOTE_F5,8}, {NOTE_G5,8},
  {REST,8}, {NOTE_E5,4}, {NOTE_C5,8}, {NOTE_D5,8}, {NOTE_B4,-4},

  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_G4,8}, {REST,4}, {NOTE_GS4,4},//23
  {NOTE_A4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_A4,2},
  {NOTE_D5,-8}, {NOTE_A5,-8}, {NOTE_A5,-8}, {NOTE_A5,-8}, {NOTE_G5,-8}, {NOTE_F5,-8},
  
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_A4,8}, {NOTE_G4,2}, //26
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_G4,8}, {REST,4}, {NOTE_GS4,4},
  {NOTE_A4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_A4,2},
  {NOTE_B4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_F5,-8}, {NOTE_E5,-8}, {NOTE_D5,-8},
  {NOTE_C5,8}, {NOTE_E4,4}, {NOTE_E4,8}, {NOTE_C4,2},

  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_G4,8}, {REST,4}, {NOTE_GS4,4},//repeats from 23
  {NOTE_A4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_A4,2},
  {NOTE_D5,-8}, {NOTE_A5,-8}, {NOTE_A5,-8}, {NOTE_A5,-8}, {NOTE_G5,-8}, {NOTE_F5,-8},
  
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_A4,8}, {NOTE_G4,2}, //26
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_G4,8}, {REST,4}, {NOTE_GS4,4},
  {NOTE_A4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_A4,2},
  {NOTE_B4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_F5,-8}, {NOTE_E5,-8}, {NOTE_D5,-8},
  {NOTE_C5,8}, {NOTE_E4,4}, {NOTE_E4,8}, {NOTE_C4,2},
  {NOTE_C5,8}, {NOTE_C5,4}, {NOTE_C5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_D5,8}, {NOTE_E5,8},
  {REST,1},

  {NOTE_C5,8}, {NOTE_C5,4}, {NOTE_C5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_D5,4}, //33
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_A4,8}, {NOTE_G4,2},
  {NOTE_E5,8}, {NOTE_E5,8}, {REST,8}, {NOTE_E5,8}, {REST,8}, {NOTE_C5,8}, {NOTE_E5,4},
  {NOTE_G5,4}, {REST,4}, {NOTE_G4,4}, {REST,4}, 
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_G4,8}, {REST,4}, {NOTE_GS4,4},
  {NOTE_A4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_A4,2},
  {NOTE_D5,-8}, {NOTE_A5,-8}, {NOTE_A5,-8}, {NOTE_A5,-8}, {NOTE_G5,-8}, {NOTE_F5,-8},
  
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_A4,8}, {NOTE_G4,2}, //40
  {NOTE_E5,8}, {NOTE_C5,4}, {NOTE_G4,8}, {REST,4}, {NOTE_GS4,4},
  {NOTE_A4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_A4,2},
  {NOTE_B4,8}, {NOTE_F5,4}, {NOTE_F5,8}, {NOTE_F5,-8}, {NOTE_E5,-8}, {NOTE_D5,-8},
  {NOTE_C5,8}, {NOTE_E4,4}, {NOTE_E4,8}, {NOTE_C4,2},
  
  //game over sound
  {NOTE_C5,-4}, {NOTE_G4,-4}, {NOTE_E4,4}, //45
  {NOTE_A4,-8}, {NOTE_B4,-8}, {NOTE_A4,-8}, {NOTE_GS4,-8}, {NOTE_AS4,-8}, {NOTE_GS4,-8},
  {NOTE_G4,8}, {NOTE_D4,8}, {NOTE_E4,-2},
  {REST, -1}, {REST, -1}  

};
int tempo = 200;

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