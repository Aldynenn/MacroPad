#include <Arduino.h>

#include <Keypad.h>

#define HID_CUSTOM_LAYOUT // set this flag to indicate that a custom layout is selected
// if the above flag is not defined, then the default US layout is used instead
#define LAYOUT_GERMAN //Cho
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

const byte ROWS = 4;
const byte COLS = 2;
char keys[ROWS][COLS] = {
  {'H', 'D'},
  {'G', 'C'}, 
  {'F', 'B'},
  {'E', 'A'} 
};

byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {4, 5};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


/* =================== PROFILE MANAGEMENT =================== */
byte currentProfile = 0;
void cycleProfiles() {
  currentProfile++;
  if (PROFILE_COUNT <= currentProfile) {
    currentProfile = 0;
  }
}


/* =============== HANDLING KEYPRESS AND HOLD =============== */
bool heldDown = false;
unsigned long lastPress = 0;
unsigned long lastHold = 0;
void handleKey(char key, KeyState state) {
  byte keyIndex = (byte)key-(byte)keys[0][0]; 
  KeyMacro macro = profiles[currentProfile].macros[keyIndex];
  switch (state) {
    case PRESSED:
      heldDown = false;
      break;
    case HOLD:
      heldDown = true;
      // macro.onHold();
      lastHold = millis();
      // leds[keyIndex].setRGB(macro.holdColor.r, macro.holdColor.g, macro.holdColor.b);
      // FastLED.show();
      Serial.print("Key ");
      Serial.print(key);
      Serial.println(" held down");
      break;
    case RELEASED:
      if (!heldDown) {
        // macro.onPress();
        lastPress = millis();
        // leds[keyIndex].setRGB(macro.pressColor.r, macro.pressColor.g, macro.pressColor.b);
        // FastLED.show();
        Serial.print("Key ");
        Serial.print(key);
        Serial.println(" pressed");
      }
      break;
  }
}


void showIdle() {
  FastLED.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    KeyColor idle = profiles[currentProfile].macros[i].idleColor;
    leds[i].setRGB(idle.r, idle.g, idle.b);
  }
  FastLED.show();
}

/* ========================= SETUP ========================== */
void setup() {
  pinMode(LED_DATA_PIN, OUTPUT);
  pinMode(ROTARY_ENCODER_A, INPUT);
  pinMode(ROTARY_ENCODER_B, INPUT);
  pinMode(ROTARY_ENCODER_SW, INPUT);

  Serial.begin(115200);

  keypad.setHoldTime(200);

  assignMacros();

  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);  
  FastLED.clear();
  FastLED.setBrightness(10);
  showIdle();
}

unsigned long lastTime = 0;
/* ========================== LOOP ========================== */
void loop() {
  if (digitalRead(ROTARY_ENCODER_SW)) {
    cycleProfiles();
  }

  if (millis() - lastPress > 250 && millis() - lastHold > 250) {
    showIdle();
  }

  if (keypad.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (keypad.key[i].stateChanged) {
        char currentKey = keypad.key[i].kchar;  
        KeyState currentState = keypad.key[i].kstate;
        handleKey(currentKey, currentState);
      }
    }
  }
  
  // if (millis() - lastTime > 1000) {
  //   lastTime = millis();
  //   Serial.print("Milliseconds since code began: ");
  //   Serial.println(millis());
  // }
}