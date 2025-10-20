#include "clay.h"
#include "global.h"

int WindowState = 0;

char TextBuffer[MAX_TEXT] = {0};

const int FONT_ID_BODY_16 = 0;
const int FONT_ID_BODY_32 = 0;

const Clay_Color COLOR_ORANGE    = (Clay_Color) {225, 138, 50, 255};
const Clay_Color COLOR_BLUE      = (Clay_Color) {111, 173, 162, 255};
const Clay_Color COLOR_LIGHT     = (Clay_Color) {224, 215, 210, 255};
const Clay_Color COLOR_BLACK     = (Clay_Color) {0, 0, 0, 255};
const Clay_Color COLOR_RED       = (Clay_Color) {220, 0, 0, 255};
const Clay_Color COLOR_GREEN     = (Clay_Color) {0, 220, 0, 255};
const Clay_Color COLOR_WHITE     = (Clay_Color) { 255, 255, 255, 255};
