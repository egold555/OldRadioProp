#include "AudioPlayer.h"
#include <SoftwareSerial.h>
#include <Servo.h> 

#define PIN_AUDIO_RX 9
#define PIN_AUDIO_TX 10

#define PIN_LED_1 6
#define PIN_CHANNEL_SERVO 11


#define AUDIO_LOOP 1
const long AUDIO_LOOP_LENGTH_MS = 528500L;


long startNextRepeat = 0;
long startLedNext = 0;
long startNextServoPos = 0;

Servo channelServo;

#define SERVO_NO_MOVEMENT_POS 88

void setup() {
  setupAudio(PIN_AUDIO_RX, PIN_AUDIO_TX);
  pinMode(PIN_LED_1, OUTPUT);

  channelServo.write(SERVO_NO_MOVEMENT_POS); //set initial servo position if desired
  channelServo.attach(PIN_CHANNEL_SERVO);

  randomSeed(analogRead(0));
}



void loop() {

  //Looping music
  long currentMillis = millis();
  if (currentMillis > startNextRepeat) {
    playAudio(AUDIO_LOOP);
    startNextRepeat = currentMillis + AUDIO_LOOP_LENGTH_MS;
  }

  //Flickering LEDS
  if (currentMillis > startLedNext) {
      analogWrite(PIN_LED_1, random(255));
      startLedNext = currentMillis + 100;
  }

  //Random servo movements
  if (currentMillis > startNextServoPos) {
      if(random(2) == 1){
        channelServo.write(SERVO_NO_MOVEMENT_POS + 5);
      } else {
        channelServo.write(SERVO_NO_MOVEMENT_POS - 5);
      }
      
      startNextServoPos = currentMillis + 100;
  }
  

}
