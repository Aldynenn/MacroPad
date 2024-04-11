#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>
#include <macros.h>


/* =================== SETTING UP KEYMAPS =================== */
const byte ROWS = 4;
const byte COLS = 4;

// char keys[ROWS][COLS] = {
//   {'A', 'B', 'C', 'D', 'E'},
//   {'F', 'G', 'H', 'I', 'J'},
//   {'K', 'L', 'M', 'N', 'O'},
//   {'P', 'Q', 'R', 'S', 'T'}
// };

// For debugging with common 4x4 button matrix
char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


/* ============== COUNTING LOOPS FOR DEBUGGING ============== */
unsigned long loopCount;
unsigned long startTime;
void averageLoopsPerSecond() {
  loopCount++;
  if ((millis() - startTime) > 5000) {
    Serial.print("Average loops per second = ");
    Serial.println(loopCount / 5);
    startTime = millis();
    loopCount = 0;
  }
}


/* ================= PAIRING MACROS TO KEYS ================= */
bool heldDown = false;
void handleKey(char key, KeyState state) {
  byte keyIndex = (byte)key-(byte)'A';
  if (state == PRESSED) {
    heldDown = false;
  }
  else if (state == HOLD) {
    heldDown = true;
    macrosOnHold[keyIndex]();
  }
  else if (state == RELEASED) {
    if (!heldDown) {
      macrosOnPress[keyIndex]();
    }
  }
}


/* ========================= SETUP ========================== */
void setup() {
  Serial.begin(115200);
  keypad.setHoldTime(200);
  loopCount = 0;
  startTime = millis();
  assignMacros();
}


/* ========================== LOOP ========================== */
void loop() {
  averageLoopsPerSecond();
  //The keypad.key[] array can have 10 active keys at max
  if (keypad.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (keypad.key[i].stateChanged) {
        char currentKey = keypad.key[i].kchar;
        KeyState currentState = keypad.key[i].kstate;
        handleKey(currentKey, currentState);
      }
    }
  }
}