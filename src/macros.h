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
void systemVolumeDown() {
    Consumer.write(MEDIA_VOLUME_DOWN);
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