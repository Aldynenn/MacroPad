# Arduino MacroPad

## Introduction

This repository contains the code to a simple macropad, consisting of 4 rows and 5 columns.

The code is mainly written for the 5V variant of the Arduino Pro Micro, but due to its simplicity, it can work with other boards, which support HID.

The project is not overly optimized, it can surely be improved if it's done without the Arduino framework, but my main focus was simplicity, rather than a smaller build size and quicker speed. 

The project is made using the PlatformIO Visual Studio Code extension.

## Macros

The macros are defined in a separate `macros.h` file in the form of void functions. Delays are inserted after each keystroke for proper behavior, however, they don't cause overly slow execution times.

### Examples

The following examples showcase how macros are written, each macro should be encased inside a function that has no return value (void)

#### Windows - Open snipping tool

```cpp
void systemScreenSnippet() {
    releaseAll();
    press(KEY_LEFT_SHIFT);
    press(KEY_LEFT_GUI);
    press('s');
    releaseAll();
}
```

#### Photoshop - Group selected layers and merge them in a separate layer

```cpp
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
```

#### Browser - Refresh page

```cpp
void browserRefresh() {
    releaseAll();
    press(KEY_F5);
    releaseAll();
}
```

#### Browser - Force refresh page (deletes cache)

```cpp
void browserForceRefresh() {
    releaseAll();
    press(KEY_LEFT_CTRL);
    press(KEY_F5);
    releaseAll();
}
```
