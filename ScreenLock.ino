#include <Arduboy.h>
#include <Keyboard.h>

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

  
  
  arduboy.display();

  prevKeys = curKeys;
}

void lockScreen() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
  delay(100);
  Keyboard.releaseAll();
}

