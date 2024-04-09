#define DELAY 10
#define DELAY_2 100
#define DELAY_3 500

//PHOTOSHOP
void photoshopExport() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press(KEY_LEFT_SHIFT); /*----------*/ delay(DELAY);
    Keyboard.press(KEY_LEFT_ALT); /*------------*/ delay(DELAY);
    Keyboard.press('W'); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
}
void photoshopHue() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press('U'); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
}
void photoshopGroupAndMerge() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press('g'); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press(','); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press('j'); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press(','); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press('e'); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
}


//DISCORD
void discordMuteToggle() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_F24); /*-----------------*/ delay(DELAY);
    Keyboard.releaseAll();
}
void discordDeafenToggle() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_F23); /*-----------------*/ delay(DELAY);
    Keyboard.releaseAll();
}


//SYSTEM
void systemVolumeUp() {
    Consumer.write(MEDIA_VOLUME_UP);
}
void systemVolumeDown() {
    Consumer.write(MEDIA_VOLUME_DOWN);
}
void systemVolumeMute() {
    Consumer.write(MEDIA_VOLUME_MUTE);
}
void systemPrintScreen() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_PRINTSCREEN); /*---------*/ delay(DELAY);
    Keyboard.releaseAll();
}
void systemScreenSnippet() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_SHIFT); /*----------*/ delay(DELAY);
    Keyboard.press(KEY_LEFT_GUI); /*------------*/ delay(DELAY);
    Keyboard.press('S'); /*---------------------*/ delay(DELAY);
    Keyboard.releaseAll();
}


//BROWSER
void browserRefresh() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_F5); /*------------------*/ delay(DELAY);
    Keyboard.releaseAll();
}
void browserForceRefresh() {
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_CTRL); /*-----------*/ delay(DELAY);
    Keyboard.press(KEY_F5); /*------------------*/ delay(DELAY);
    Keyboard.releaseAll();
}