# ArduboyLock
Turns an Arduboy into a remote control for locking a computer!

The Arduboy pretends to be a keyboard, and sends keyboard shortcuts whenever you press buttons on it. It has commands to lock the computer, as well as switch between multiple desktops.

This is primarily designed for the Linux (should work with Ubuntu/Debian). Read further for instructions on to what to do for other operating systems.

## Controls:

- A/B: Lock the computer
- Left/Right: Switch desktop
- Down: Show all windows
- Up: Show all

## Other operating systems

The keyboard commands work necessarily work on different operating systems. But if you know what the equivalent shortcut is for your OS, you can edit the .ino file to make it work for that too. Just change what keys the `startLock` and `startMove` functions use.

This is what they do at the moment:

`startLock` sends CTRL, ALT and L

```
void startLock() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
  arduboy.tunes.tone(785, 20);
}
```

`startMove` secnds CTRL, ALT and the arrow key corresponding the to the key on the D-pad.

```
void startMove(int key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
}
```
