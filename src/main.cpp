#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FastLED.h>
#include <macros.h>

/* ==================== SETTING UP LEDS ===================== */
#define LED_DATA_PIN 15
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
bool ledState = false;


/* =================== SETTING UP DISPLAY =================== */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C //See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/* =================== SETTING UP KEYMAPS =================== */
const byte ROWS = 2;
const byte COLS = 4;

// For debugging with common 4x4 button matrix
// char keys[ROWS][COLS] = {
//   {'A', 'B', 'C', 'D'},
//   {'E', 'F', 'G', 'H'},
//   {'I', 'J', 'K', 'L'},
//   {'M', 'N', 'O', 'P'}
// };

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
    Serial.print("Average loops per second = ");
    Serial.println(loopCount);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Loops per second:");
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print(loopCount);
    display.display();
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
    macros[keyIndex].onHold();
  }
  else if (state == RELEASED) {
    if (!heldDown) {
      macros[keyIndex].onPress();
    }
  }
}


/* ========================= SETUP ========================== */
void setup() {
  pinMode(LED_DATA_PIN, OUTPUT);
  Serial.begin(115200);
  keypad.setHoldTime(200);
  loopCount = 0;
  startTime = millis();
  assignMacros();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();

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
        // FastLED.clear();
        // leds[(byte)currentKey-(byte)'A'] = CRGB::White;
        // FastLED.show();
      }
    }
  }
}