/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-melody-example
   Library References: https://arduinogetstarted.com/tutorials/arduino-buzzer-library

   This example uses a piezo buzzer:
   + plays a melody once on background each time a button is pressed
   + stops playing a melody when another button is pressed
   + without using delay() function, this is a non-blocking example
*/

#include <asyncBuzzer.h> // asyncBuzzer library

const int START_BUTTON_PIN = 7;
const int STOP_BUTTON_PIN  = 8;
const int BUZZER_PIN = 3;

int lastStartButtonState = HIGH; // the previous state from the input pin
int lastStopButtonState  = HIGH; // the previous state from the input pin

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

void setup() {
  Serial.begin(9600);
  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(STOP_BUTTON_PIN,  INPUT_PULLUP);
}

void loop() {
  buzzer.loop(); // MUST call the buzzer.loop() function in loop()

  int startButtonState = digitalRead(START_BUTTON_PIN);
  int stopButtonState  = digitalRead(STOP_BUTTON_PIN);

  if (lastStartButtonState == HIGH && startButtonState == LOW) {
    Serial.println("The START button is pressed");
    if (buzzer.getState() == BUZZER_IDLE) {
      int length = sizeof(melody) / sizeof(melody[0]);
      buzzer.playMelody(melody, 240, length); // playing
    }
  }

  if (lastStopButtonState == HIGH && stopButtonState == LOW) {
    Serial.println("The STOP button is pressed");
    if (buzzer.getState() != BUZZER_IDLE) {
      buzzer.stop() ; // stop
    }
  }

  lastStartButtonState = startButtonState;
  lastStopButtonState  = stopButtonState;
}