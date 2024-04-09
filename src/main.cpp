#include <Arduino.h>
#include <Keypad.h>
#include <HID-Project.h>
#include <macros.h>

const byte ROWS = 4;
const byte COLS = 5;
char keys[ROWS][COLS] = {
  {'0', '1', '2', '3', '4'},
  {'5', '6', '7', '8', '9'},
  {'A', 'B', 'C', 'D', 'E'},
  {'F', 'G', 'H', 'I', 'J'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {10, 9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long loopCount;
unsigned long startTime;
String msg;

void setup() {
  Serial.begin(115200);
  loopCount = 0;
  startTime = millis();
  msg = "";
}

void loop() {
  loopCount++;
  if ((millis() - startTime) > 5000) {
    Serial.print("Average loops per second = ");
    Serial.println(loopCount / 5);
    startTime = millis();
    loopCount = 0;
  }
  
  //The keypad.key[] array can have 10 active keys at max
  if (keypad.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (keypad.key[i].stateChanged) {
        switch (keypad.key[i].kstate) {
          case PRESSED:
            msg = " PRESSED.";
            break;
          case HOLD:
            msg = " HOLD.";
            break;
          case RELEASED:
            msg = " RELEASED.";
            break;
          case IDLE:
            msg = " IDLE.";
        }
        Serial.print("Key ");
        Serial.print(keypad.key[i].kchar);
        Serial.println(msg);
      }
    }
  }
}