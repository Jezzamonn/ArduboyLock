#include <Arduboy.h>
#include <Keyboard.h>

#include "bitmaps.h"

#define LOCK_WIDTH 48
#define LOCK_HEIGHT 56

uint16_t frameCount = 0;
uint16_t animateCount = 0;

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

int lockKeyDown = false;

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

  if (!lockKeyDown && (curKeys.a || curKeys.b)) {
    lockKeyDown = true;
    startLock();
  }
  if (lockKeyDown && !(curKeys.a || curKeys.b)) {
    lockKeyDown = false;
    Keyboard.releaseAll();
  }

  if (!prevKeys.left && curKeys.left) {
    startMove(KEY_LEFT_ARROW);
  }

  if (!prevKeys.right && curKeys.right) {
    startMove(KEY_RIGHT_ARROW);
  }
  
  if (!prevKeys.up && curKeys.up) {
    startMove(KEY_UP_ARROW);
  }
 
  if (!prevKeys.down && curKeys.down) {
    startMove(KEY_DOWN_ARROW);
  }

  if ((prevKeys.left && !curKeys.left) ||
      (prevKeys.right && !curKeys.right) ||
      (prevKeys.up && !curKeys.up) ||
      (prevKeys.down && !curKeys.down)) {
    Keyboard.releaseAll();
  }

  if (lockKeyDown || curKeys.left || curKeys.right || curKeys.up || curKeys.down) {
    animateCount = 30;
  }
  
  if (animateCount > 0) {
    animateCount --;

    arduboy.clearDisplay();
    if (animateCount > 0) {
      drawBackground();
      drawLock();
    }
    arduboy.display();
  }

  frameCount += 4;

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
    int8_t dy = y - HEIGHT / 2;
    for (uint8_t x = 0; x < WIDTH; x ++) {
      int8_t dx = x - WIDTH / 2;

      if (dx * dx + 2 * dy * dy < 160 * animateCount &&
          ((x + y) & 0b111) == ((frameCount >> 2) & 0b111)) {
        arduboy.drawPixel(x, y, WHITE);
      }
    }
  }
}

void startLock() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
  arduboy.tunes.tone(785, 20);
}

void startMoveLeft() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_ARROW);
}

void startMoveRight() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_RIGHT_ARROW);
}

void startMove(int key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
}
