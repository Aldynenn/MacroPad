#define KEY_COUNT 20

#define DELAY 10
#define DELAY_2 100
#define DELAY_3 500

template<typename T>
inline void press(T key, int mils = DELAY) {
    Keyboard.press(key);
    delay(mils);
}

template<typename T>
inline void release(T key, int mils = 0) {
    Keyboard.release(key);
    delay(mils);
}

inline void releaseAll() {
    Keyboard.releaseAll();
}

//PHOTOSHOP
void photoshopExport() {
    releaseAll();
    press(KEY_LEFT_CTRL);
    press(KEY_LEFT_SHIFT);
    press(KEY_LEFT_ALT);
    press('w');
    releaseAll();
}
void photoshopHue() {
    releaseAll();
    press(KEY_LEFT_CTRL);
    press('u');
    releaseAll();
}
void photoshopGroupAndMerge() {
    releaseAll();
    press(KEY_LEFT_CTRL);
    press('g');
    release('g');
    press(',');
    release(',');
    press('j');
    release('j');
    press(',');
    release(',');
    press('e');
    releaseAll();
}
void photoshopCameraRaw() {
    releaseAll();
    press(KEY_LEFT_SHIFT);
    press(KEY_LEFT_CTRL);
    press('a');
    releaseAll();
}


//DISCORD
void discordMuteToggle() {
    releaseAll();
    press(KEY_F24);
    releaseAll();
}
void discordDeafenToggle() {
    releaseAll();
    press(KEY_F23);
    releaseAll();
}


//SYSTEM
void systemVolumeUp() {
    Consumer.write(MEDIA_VOLUME_UP);
}
void systemVolumeUpMultiple() {
    for (byte i = 0; i < 5; i++) {
        systemVolumeUp();
    }
}
void systemVolumeDown() {
    Consumer.write(MEDIA_VOLUME_DOWN);
}
void systemVolumeDownMultiple() {
    for (byte i = 0; i < 5; i++) {
        systemVolumeDown();
    }
}
void systemVolumeMuteToggle() {
    Consumer.write(MEDIA_VOLUME_MUTE);
}
void systemScreenSnippet() {
    releaseAll();
    press(KEY_LEFT_SHIFT);
    press(KEY_LEFT_GUI);
    press('s');
    releaseAll();
}


//VS CODE
void moveLineUp() {
    releaseAll();
    press(KEY_LEFT_ALT);
    press(KEY_UP_ARROW);
    releaseAll();
}
void moveLineDown() {
    releaseAll();
    press(KEY_LEFT_ALT);
    press(KEY_DOWN_ARROW);
    releaseAll();
}
void cloneLineUp() {
    releaseAll();
    press(KEY_LEFT_SHIFT);
    press(KEY_LEFT_ALT);
    press(KEY_UP_ARROW);
    releaseAll();
}
void cloneLineDown() {
    releaseAll();
    press(KEY_LEFT_SHIFT);
    press(KEY_LEFT_ALT);
    press(KEY_DOWN_ARROW);
    releaseAll();
}


//BROWSER
void browserRefresh() {
    releaseAll();
    press(KEY_F5);
    releaseAll();
}
void browserForceRefresh() {
    releaseAll();
    press(KEY_LEFT_CTRL);
    press(KEY_F5);
    releaseAll();
}


/* ============== PAIRING MACROS TO KEY INDEXES ============= */
void placeholder() {
    Serial.println("No macro assigned for this event");
}


struct KeyColor {
    byte r;
    byte g;
    byte b;
};
struct KeyMacro {
    void (*onPress)();
    void (*onHold)();
    String name;
    KeyColor idleColor;
    KeyColor pressColor;
    KeyColor holdColor;
};


KeyMacro macros[KEY_COUNT];

void (*macrosOnPress[KEY_COUNT])();
void (*macrosOnHold[KEY_COUNT])();

void assignMacros() {
    //MACROS THAT SHOULD RUN WHEN KEY IS QUICKLY PRESSED
    macrosOnPress[0] = systemVolumeUp;
    macrosOnPress[1] = systemVolumeDown;
    macrosOnPress[2] = systemVolumeMuteToggle;
    macrosOnPress[3] = discordMuteToggle;
    macrosOnPress[4] = browserRefresh;
    macrosOnPress[5] = photoshopGroupAndMerge;
    macrosOnPress[6] = moveLineUp;
    macrosOnPress[7] = moveLineDown;

    //MACROS THAT SHOULD RUN WHEN KEY IS HELD DOWN
    macrosOnHold[0] = systemVolumeUpMultiple;
    macrosOnHold[1] = systemVolumeDownMultiple;
    macrosOnHold[3] = discordDeafenToggle;
    macrosOnHold[4] = browserForceRefresh;
    macrosOnHold[5] = photoshopCameraRaw;
    macrosOnHold[6] = cloneLineUp;
    macrosOnHold[7] = cloneLineDown;

    for (int i = 0; i < KEY_COUNT; i++) {
        if (macrosOnPress[i] == NULL) {
            macrosOnPress[i] = placeholder;
        }
        if (macrosOnHold[i] == NULL) {
            macrosOnHold[i] = placeholder;
        }
    }
}