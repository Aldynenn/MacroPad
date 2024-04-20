#define KEY_COUNT 8
#define PROFILE_COUNT 2

//STANDARD DELAYS, CHANGE THESE TO SUIT YOUR PREFERENCES
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
    Serial.println("Placeholder Macro Ran | No macro assigned for this event!");
}

class KeyColor {
    public:
        byte r;
        byte g;
        byte b;
        KeyColor(byte r, byte g, byte b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }
        KeyColor() {
            this->r = 0;
            this->g = 0;
            this->b = 0;
        }
};

class KeyMacro {
    public:
        void (*onPress)();
        void (*onHold)();
        String pressName;
        String holdName;
        KeyColor idleColor;
        KeyColor pressColor;
        KeyColor holdColor;
        KeyMacro(void (*onPress)(), void (*onHold)(), String pressName, String holdName, KeyColor idleColor, KeyColor pressColor, KeyColor holdColor) {
            this->onPress = onPress;
            this->onHold = onHold;
            this->pressName = pressName;
            this->holdName = holdName;
            this->idleColor = idleColor;
            this->pressColor = pressColor;
            this->holdColor = holdColor;
        }
        KeyMacro(void (*onPress)(), String pressName, KeyColor idleColor, KeyColor pressColor, KeyColor holdColor) {
            this->onPress = onPress;
            this->onHold = placeholder;
            this->pressName = pressName;
            this->idleColor = idleColor;
            this->pressColor = pressColor;
            this->holdColor = holdColor;
        }
        KeyMacro() {
            this->onPress = placeholder;
            this->onHold = placeholder;
            this->pressName = "Unnamed Macro";
            this->holdName = "Unnamed Macro";
            this->idleColor = KeyColor(255, 0, 0);
            this->pressColor = KeyColor(0, 255, 0);
            this->holdColor = KeyColor(0, 0, 255);
        }
        void press() {
            Serial.println(pressName);
            onPress();
        }
        void hold() {
            Serial.println(holdName);
            onHold();
        }
};

class Profile {
    public:
        String name;
        KeyMacro macros[KEY_COUNT];

        Profile(String name, KeyMacro macros[KEY_COUNT]) {
            this->name = name;
            for (int i = 0; i < KEY_COUNT; i++) {
                this->macros[i] = macros[i];
            }
        }
        Profile(String name) {
            this->name = name;
            for (int i = 0; i < KEY_COUNT; i++) {
                this->macros[i] = KeyMacro();
            }
        }
        Profile() {
            this->name = "Unnamed Profile";
            for (int i = 0; i < KEY_COUNT; i++) {
                this->macros[i] = KeyMacro();
            }
        }
};

Profile profiles[2];

void assignMacros() {
    profiles[0] = Profile("Default Profile");
    profiles[0].macros[0] = KeyMacro(systemVolumeUp, systemVolumeUpMultiple, "System Volume Up", "System Volume Up X10", KeyColor(0, 255, 255), KeyColor(0, 255, 127), KeyColor(63, 255, 127));
    profiles[0].macros[1] = KeyMacro(systemVolumeDown, systemVolumeDownMultiple, "System Volume Down", "System Volume Down X10", KeyColor(0, 255, 255), KeyColor(0, 127, 255), KeyColor(63, 127, 255));
    profiles[0].macros[2] = KeyMacro(systemVolumeMuteToggle, "System Volume Mute Toggle", KeyColor(255, 0, 0), KeyColor(0, 255, 0), KeyColor(0, 0, 255));
    profiles[0].macros[3] = KeyMacro(discordMuteToggle, discordDeafenToggle, "Discord Mute Toggle", "Discord Deafen Toggle", KeyColor(255, 0, 0), KeyColor(0, 255, 0), KeyColor(0, 0, 255));
    profiles[0].macros[4] = KeyMacro(browserRefresh, browserForceRefresh, "Browser Refresh", "Browser Force Refresh", KeyColor(255, 0, 0), KeyColor(0, 255, 0), KeyColor(0, 0, 255));
    profiles[0].macros[5] = KeyMacro();
    profiles[0].macros[6] = KeyMacro(moveLineUp, cloneLineUp, "Move Line Up", "Clone Line Up", KeyColor(255, 0, 0), KeyColor(0, 255, 0), KeyColor(0, 0, 255));
    profiles[0].macros[7] = KeyMacro(moveLineDown, cloneLineDown, "Move Line Down", "Clone Line Down", KeyColor(255, 0, 0), KeyColor(0, 255, 0), KeyColor(0, 0, 255));
}