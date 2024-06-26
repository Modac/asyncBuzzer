/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-beep-example
   Library References: https://arduinogetstarted.com/tutorials/arduino-buzzer-library

   This example uses a piezo buzzer:
   + generates a 100ms beep on background when a button is pressed 
   + without using delay() function, this is a non-blocking example
*/

#include <asyncBuzzer.h> // asyncBuzzer library

const int BUTTON_PIN = 7;
const int BUZZER_PIN = 3;

int lastButtonState = HIGH; // the previous state from the input pin

asyncBuzzer buzzer(BUZZER_PIN); // create asyncBuzzer object that attach to a pin;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  buzzer.loop(); // MUST call the buzzer.loop() function in loop()

  int currentState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentState == LOW) {
    Serial.println("The button is pressed");
    buzzer.beep(2000, 100, 200, 2, false); // generates two 2kHz, 100ms beeps with 200ms pause inbetween and no initial delay
  }

  lastButtonState = currentState;
}