#include "AudioPlayer.h"
#include <SoftwareSerial.h>


#define PIN_AUDIO_RX 9
#define PIN_AUDIO_TX 10

#define AUDIO_LOOP 1

const long AUDIO_LOOP_LENGTH_MS = 528500L;

long startNextRepeat = 0;

#define LED_1 6

void setup() {
  setupAudio(PIN_AUDIO_RX, PIN_AUDIO_TX);
  pinMode(LED_1, OUTPUT);
}

long startLedNext = 0;

void loop() {

  //Looping music
  long currentMillis = millis();
  if (currentMillis > startNextRepeat) {
    playAudio(AUDIO_LOOP);
    startNextRepeat = currentMillis + AUDIO_LOOP_LENGTH_MS;
  }

  if (currentMillis > startLedNext) {
      analogWrite(LED_1, random(255));
      startLedNext = currentMillis + 100;
  }
  

}
