/*
 * Copyright (c) 2019, ArduinoGetStarted.com. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of the ArduinoGetStarted.com nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ARDUINOGETSTARTED.COM "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARDUINOGETSTARTED.COM BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <asyncBuzzer.h>

asyncBuzzer::asyncBuzzer(int pin) {
	_buzzerPin   = pin;
	_buzzerState = BUZZER_IDLE;

	_beepFrequency = 0;
	_delayTime = 0;
	_beepTime  = 0;
	_beepReps = 0;

	_startTime = 0;

	_melody = 0;
	_wholeNote = 0;
	_melodyLength  = 0;
	_melodyIndex   = 0;
	_notePauseTime = 0;

	pinMode(_buzzerPin, OUTPUT);
}


void asyncBuzzer::stop(void){
	noTone(_buzzerPin);

	_buzzerState = BUZZER_IDLE;
}

void asyncBuzzer::beep(unsigned int frequency, unsigned long beepTime) {
	beep(frequency, beepTime, 0, 1, false);
}

void asyncBuzzer::beep(unsigned int frequency, unsigned long beepTime, unsigned long delay, unsigned int repetitions, bool initialDelay) {
	_beepFrequency = frequency;
	_delayTime = delay;
	_beepTime  = beepTime;
	_beepReps = repetitions;
	if (initialDelay) {
		_buzzerState = BUZZER_BEEP_DELAY;
	} else {
		_buzzerState = BUZZER_BEEPING;
		tone(_buzzerPin, _beepFrequency);
	}
	_startTime = millis();
}

void asyncBuzzer::playMelody(Note *melody, int tempo, int length) {
	_melody = melody;
	_melodyLength  = length;
	_wholeNote = (60000 * 4) / tempo;
	_melodyIndex   = 0;
	_notePauseTime = 0;

	_buzzerState = BUZZER_MELODY;
	_startTime = millis();
}

int asyncBuzzer::getState(void) {
	return _buzzerState;
}

void asyncBuzzer::loop(void) {

	switch(_buzzerState) {
		case BUZZER_IDLE:
			break;

		case BUZZER_BEEP_DELAY:
			if ((unsigned long)(millis() - _startTime) >= _delayTime) {
				_buzzerState = BUZZER_BEEPING;
				_startTime = millis();

				tone(_buzzerPin, _beepFrequency);
			}

			break;

		case BUZZER_BEEPING:
			if ((unsigned long)(millis() - _startTime) >= _beepTime) {
				noTone(_buzzerPin);
				_beepReps--;
				if (_beepReps > 0) {
					_buzzerState = BUZZER_BEEP_DELAY;
					_startTime = millis();
				} else {
					_buzzerState = BUZZER_IDLE;
				}
			}

			break;

		case BUZZER_MELODY:
			if(_melodyIndex < _melodyLength) {
				if(!_notePauseTime) {
					int divider = _melody[_melodyIndex]._duration;
					int duration = _wholeNote>>2;
					if (divider > 0) {
						duration = _wholeNote/divider;
					} else if (divider < 0) {
						duration = _wholeNote/abs(divider);
						// almost the same as *= 1.5 but hopefully faster
						duration += duration>>1;
					}
					_notePauseTime = duration;
					// Uncomment one of the following lines to add the pause after the full note duration
					//_notePauseTime += duration>>2; // almost the same as *= 1.25
					//_notePauseTime += duration>>3; // almost the same as *= 1.125
					//_notePauseTime += (duration*42598)>>15 // almost the same as *= 1.3 (from 1-1000: max delta=1, deviation percent=10%)

					// Uncomment this line to have the pause be part of the note duration  
					//duration -= duration>>3; 														// bad approx for *=0.9, more like 0.875 (from 1-1000: max delta=25, deviation percent=96.1%)
        			//duration -= duration>>4; duration -= duration>>5; duration -= duration>>6;	// "better" approx for *=0.9 (from 1-1000: max delta=5, deviation percent=83%)
        			duration = (duration * 58982)>>16;												// "best" approx for *=0.9 (from 1-1000: max delta=1, deviation percent=10%)

					tone(_buzzerPin, _melody[_melodyIndex]._frequency, duration);

					_startTime = millis();
				}

				if ((unsigned long)(millis() - _startTime) >= _notePauseTime) {
					noTone(_buzzerPin); // stop the tone playing:
					_notePauseTime = 0;
					_melodyIndex++; // play next node
				}
			} else {
				noTone(_buzzerPin);
				_buzzerState = BUZZER_IDLE;
			}

			break;

		default:
			break;
	}
}