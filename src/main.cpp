#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>
#include <macros.h>


/* =================== SETTING UP KEYMAPS =================== */
const byte ROWS = 4;
const byte COLS = 5;

char keys[ROWS][COLS] = {
  {'0', '1', '2', '3', '4'},
  {'5', '6', '7', '8', '9'},
  {'A', 'B', 'C', 'D', 'E'},
  {'F', 'G', 'H', 'I', 'J'}
};

// For debugging with common 4x4 button matrix
// char keys[ROWS][COLS] = {
//   {'0', '1', '2', '3'},
//   {'4', '5', '6', '7'},
//   {'8', '9', 'A', 'B'},
//   {'C', 'D', 'E', 'F'}
// };

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
void handleKey(char key, KeyState state) {
  switch (key) {
  case '0':
    if (state == PRESSED) {
      photoshopGroupAndMerge();
    }
    else if (state == HOLD) {
    }
  break;
  case '1':
    if (state == PRESSED) {
    }
    else if (state == HOLD) {
    }
  break;
  case '2':
    if (state == PRESSED) {
    }
    else if (state == HOLD) {
    }
  break;
  case '3':
    if (state == PRESSED) {
    }
    else if (state == HOLD) {
    }
  break;
  case '4':
    if (state == PRESSED) {
    }
    else if (state == HOLD) {
    }
  break;
  case '5':
  break;
  case '6':
  break;
  case '7':
  break;
  case '8':
  break;
  case '9':
  break;
  case 'A':
  break;
  case 'B':
  break;
  case 'C':
  break;
  case 'D':
  break;
  case 'E':
  break;
  case 'F':
  break;
  case 'G':
  break;
  case 'H':
  break;
  case 'I':
  break;
  case 'J':
  break;
  default:
  break;
  }
}


/* ========================= SETUP ========================== */
void setup() {
  Serial.begin(115200);
  loopCount = 0;
  startTime = millis();
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