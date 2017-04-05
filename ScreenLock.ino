#include <Arduboy.h>
#include <Keyboard.h>

#include "bitmaps.h"

#define LOCK_WIDTH 48
#define LOCK_HEIGHT 56

uint16_t frameCount = 0;

struct Keystate {
  bool a = false;
  bool b = false;
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
};

Keystate prevKeys;
Keystate curKeys;

Arduboy arduboy;

int keyDown = false;

void setup() {
  // put your setup code here, to run once:
  arduboy.start();
  arduboy.setFrameRate(60);
  
  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(arduboy.nextFrame()))
    return;
  
  curKeys.a = arduboy.pressed(A_BUTTON);
  curKeys.b = arduboy.pressed(B_BUTTON);
  curKeys.left = arduboy.pressed(LEFT_BUTTON);
  curKeys.right = arduboy.pressed(RIGHT_BUTTON);
  curKeys.up = arduboy.pressed(UP_BUTTON);
  curKeys.down = arduboy.pressed(DOWN_BUTTON);

  if (!keyDown && curKeys.a || curKeys.b ||
    curKeys.left || curKeys.right || curKeys.up || curKeys.down) {

    keyDown = true;
    startLock();
  }
  if (keyDown && !(curKeys.a || curKeys.b ||
    curKeys.left || curKeys.right || curKeys.up || curKeys.down)) {

    keyDown = false;
    endLock();
  }
  
  arduboy.clearDisplay();

  drawBackground();
  drawLock();
  
  arduboy.display();

  if (keyDown) {
    frameCount -= 4;
  }
  else {
    frameCount ++;
  }
  prevKeys = curKeys;
}

void drawLock() {
  arduboy.drawBitmap((WIDTH - LOCK_WIDTH) / 2, (HEIGHT - LOCK_HEIGHT) / 2,
              lock_mask, LOCK_WIDTH, LOCK_HEIGHT, BLACK);
  arduboy.drawBitmap((WIDTH - LOCK_WIDTH) / 2, (HEIGHT - LOCK_HEIGHT) / 2,
              lock, LOCK_WIDTH, LOCK_HEIGHT, WHITE);
}

void drawBackground() {
  for (uint8_t y = 0; y < HEIGHT; y ++) {
    for (uint8_t x = 0; x < WIDTH; x ++) {
      if (((x + y) & 0b111) == ((frameCount >> 2) & 0b111)) {
        arduboy.drawPixel(x, y, WHITE);
      }
    }
  }
}

void startLock() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
}

void endLock() {
  Keyboard.releaseAll();
}

