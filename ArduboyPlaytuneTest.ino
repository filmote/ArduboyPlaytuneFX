// Sketch for testing the ArduboyTones library

#include <Arduboy2.h>
#include "src/ArduboyPlaytuneFX.h"
#include <ArduboyFX.h>
#include "fxdata/fxdata.h"

Arduboy2 arduboy;
uint8_t buffer[16]; 
ArduboyPlaytuneFX tunes(arduboy.audio.enabled, buffer);

#define BUTTON_DELAY 200

int16_t logoPos = 128;

const byte ThemePROGMEM[] PROGMEM = {
0x90,52, 1,27, 0x91,64, 0,141, 0x81, 0,141, 0x91,66, 0,141, 0x81, 0,141, 0x91,64, 0,141, 0x81, 0,141, 0x91,67,
0,141, 0x81, 0,141, 0x91,66, 0,141, 0x81, 0,141, 0x91,64, 0,141, 0x81, 0,141, 0x91,66, 0,141, 0x80, 0x81, 0,141,
0x90,50, 1,27, 0x91,64, 0,141, 0x81, 0,141, 0x91,66, 0,141, 0x81, 0,141, 0x91,64, 0,141, 0x81, 0,141, 0x91,67,
0,141, 0x81, 0,141, 0x91,66, 0,141, 0x81, 0,141, 0x91,64, 0,141, 0x81, 0,141, 0x91,66, 0,141, 0x81, 0,141,
0x91,48, 0x80, 1,27, 0x90,64, 0,141, 0x80, 0,141, 0x90,66, 0,141, 0x80, 0,141, 0x90,64, 0,141, 0x80, 0,141,
0x90,67, 0,141, 0x80, 0,141, 0x90,66, 0,141, 0x80, 0,141, 0x90,64, 0,141, 0x80, 0,141, 0x90,66, 0,141, 0x80,
0,141, 0x90,50, 0x81, 1,27, 0x91,64, 0,141, 0x81, 0,141, 0x91,66, 0,141, 0x81, 0,141, 0x91,64, 0,141, 0x81,
0,141, 0x91,71, 0,141, 0x81, 0,141, 0x91,69, 0,141, 0x81, 0,141, 0x91,67, 0,141, 0x81, 0,141, 0x91,66, 0,141,
0x81, 0,141, 0x80,
0xE0
};

void setup() {
  
  arduboy.begin();

  arduboy.audio.begin();
  tunes.initChannel(PIN_SPEAKER_1);
  tunes.initChannel(PIN_SPEAKER_2);    

  FX::disableOLED();
  FX::begin(FX_DATA_PAGE);
}

void loop() {

  if (!arduboy.nextFrame()) return; 
  arduboy.pollButtons();

  tunes.fillBufferFromFX();

  arduboy.setCursor(0,0);
  arduboy.print("From FX\nA: Start / Stop\n\n");
  arduboy.print("From PROGMEM\nB: Start / Stop\n");

  if (arduboy.justPressed(A_BUTTON)) {
    if (tunes.playing()) {
      tunes.stopScore();
    }
    else {
      tunes.playScoreFromFX(Theme, Theme_Len);
    }
  }

  if (arduboy.justPressed(B_BUTTON)) {
    if (tunes.playing()) {
      tunes.stopScore();
    }
    else {
      tunes.playScore(ThemePROGMEM);
    }
  }

  FX::drawBitmap(logoPos, 48, fxLogo, 0, dbmNormal);

  logoPos--;
  if (logoPos == -116) logoPos = 128;

  FX::enableOLED();
  arduboy.display(CLEAR_BUFFER);
  FX::disableOLED();

}
