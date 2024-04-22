#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>
#include <FastLED.h>
#include <macros.h>

/* ===================== ROTARY ENCODER ===================== */
#define ROTARY_ENCODER_A 10
#define ROTARY_ENCODER_B 16
#define ROTARY_ENCODER_SW 14


/* ==================== SETTING UP LEDS ===================== */
#define LED_DATA_PIN 15
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
bool ledState = false;


/* =================== SETTING UP KEYMAPS =================== */
// For debugging with common 4x4 button matrix:
// const byte ROWS = 4;
// const byte COLS = 4;
// char keys[ROWS][COLS] = {
//   {'A', 'B', 'C', 'D'},
//   {'E', 'F', 'G', 'H'},
//   {'I', 'J', 'K', 'L'},
//   {'M', 'N', 'O', 'P'}
// };

const byte ROWS = 2;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'}
};

byte rowPins[ROWS] = {5, 4};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


/* ============== COUNTING LOOPS FOR DEBUGGING ============== */
unsigned long loopCount;
unsigned long startTime;
void averageLoopsPerSecond() {
  loopCount++;
  if ((millis() - startTime) > 1000) {
    Serial.print("AVG loops/s: ");
    Serial.println(loopCount);
    startTime = millis();
    loopCount = 0;
  }
}


/* =============== HANDLING KEYPRESS AND HOLD =============== */
bool heldDown = false;
byte currentProfile = 0;
void handleKey(char key, KeyState state) {
  byte keyIndex = (byte)key-(byte)'A'; 
  if (state == PRESSED) {
    heldDown = false;
  }
  else if (state == HOLD) {
    heldDown = true;
    profiles[currentProfile].macros[keyIndex].hold();
  }
  else if (state == RELEASED) {
    if (!heldDown) {
      profiles[currentProfile].macros[keyIndex].press();
    }
  }
}


/* ========================= SETUP ========================== */
void setup() {
  pinMode(LED_DATA_PIN, OUTPUT);
  pinMode(ROTARY_ENCODER_A, INPUT);
  pinMode(ROTARY_ENCODER_B, INPUT);
  pinMode(ROTARY_ENCODER_SW, INPUT);

  Serial.begin(115200);
  loopCount = 0;
  startTime = millis();

  keypad.setHoldTime(200);

  assignMacros();

  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);  
  FastLED.clear();
  FastLED.setBrightness(10);
  FastLED.show();
}


/* ========================== LOOP ========================== */
void loop() {
  averageLoopsPerSecond();
  if (keypad.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (keypad.key[i].stateChanged) {
        char currentKey = keypad.key[i].kchar;  
        KeyState currentState = keypad.key[i].kstate;
        handleKey(currentKey, currentState);
        FastLED.clear();
        leds[(byte)currentKey-(byte)'A'] = CRGB::White;
        FastLED.show();
      }
    }
  }
}