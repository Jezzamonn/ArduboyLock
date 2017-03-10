#include <Arduboy.h>
#include <Keyboard.h>

#include "bitmaps.h"

#define LOCK_WIDTH 48
#define LOCK_HEIGHT 56

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

  if (curKeys.a && !prevKeys.a) {
    lockScreen();
  }
  if (curKeys.b && !prevKeys.b) {
    lockScreen();
  }
  if (curKeys.left && !prevKeys.left) {
    lockScreen();
  }
  if (curKeys.right && !prevKeys.right) {
    lockScreen();
  }
  if (curKeys.up && !prevKeys.up) {
    lockScreen();
  }
  if (curKeys.down && !prevKeys.down) {
    lockScreen();
  }
  
  arduboy.clearDisplay();

  drawBackground();
  drawLock();
  
  arduboy.display();

  prevKeys = curKeys;
}

void drawLock() {
  arduboy.drawBitmap((WIDTH - LOCK_WIDTH) / 2, (HEIGHT - LOCK_HEIGHT) / 2,
              lock_mask, LOCK_WIDTH, LOCK_HEIGHT, BLACK);
  arduboy.drawBitmap((WIDTH - LOCK_WIDTH) / 2, (HEIGHT - LOCK_HEIGHT) / 2,
              lock, LOCK_WIDTH, LOCK_HEIGHT, WHITE);
}

void drawBackground() {
  for (int y = 0; y < HEIGHT; y ++) {
    for (int x = 0; x < WIDTH; x ++) {
      if (((x + y) & 0b111) == 0) {
        arduboy.drawPixel(x, y, WHITE);
      }
    }
  }
}

void lockScreen() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
  delay(100);
  Keyboard.releaseAll();
}

