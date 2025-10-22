#include "clay.h"
#include "styles.h"
#include "global.h"

/* Parent windows */
const Clay_LayoutConfig TTBParentWindow = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)},
    .padding = { 8, 8, 8, 8},
    .childGap = 40,
    .childAlignment =  {  CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = CLAY_TOP_TO_BOTTOM
};

const Clay_LayoutConfig LTRParentWindow = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)},
    .padding = { 0, 0, 0, 0},
    .childGap = 8,
    .childAlignment =  {  CLAY_ALIGN_X_LEFT, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = CLAY_LEFT_TO_RIGHT
};

/* Sidebar content */

const Clay_LayoutConfig SidebarWindow = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_FIXED(250), CLAY_SIZING_GROW(0)},
    .padding = { 8, 8, 8, 8},
    .childGap = 0,
    .childAlignment =  {  CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP },
    .layoutDirection = CLAY_TOP_TO_BOTTOM
};

const Clay_ElementDeclaration SidebarWindowStyle = (Clay_ElementDeclaration) {
    SidebarWindow,
    .backgroundColor = {15, 50, 150, 255},
    .cornerRadius = CLAY_CORNER_RADIUS(10)
};

/* Content window*/

const Clay_LayoutConfig ContentWindow = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)},
    .padding = { 16, 16, 16, 16},
    .childGap = 40,
    .childAlignment =  {  CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP },
    .layoutDirection = CLAY_TOP_TO_BOTTOM
};

const Clay_ElementDeclaration ContentWindowStyle = (Clay_ElementDeclaration) {
    ContentWindow,
    .backgroundColor = {0, 0, 0, 255},
    .cornerRadius = CLAY_CORNER_RADIUS(10)
};

const Clay_LayoutConfig HeadLabelWindow = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_FIXED(400), CLAY_SIZING_FIXED(100) },
    .padding = { 8, 8, 8, 8 },
    .childGap = 16,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = CLAY_TOP_TO_BOTTOM
};

const Clay_LayoutConfig SingleLineTextContainer = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_FIXED(214), CLAY_SIZING_FIXED(32) },
    .padding = { 8, 8, 8, 8 },
    .childGap = 16,
    .childAlignment =  { CLAY_ALIGN_X_LEFT, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = CLAY_TOP_TO_BOTTOM
};

/* Buttons */

const Clay_LayoutConfig MainButtonLayout = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_FIXED(200), CLAY_SIZING_FIXED(50) },
    .padding = { 8, 8, 8, 8 },
    .childGap = 16,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = CLAY_TOP_TO_BOTTOM
};

const Clay_TextElementConfig ButtonLabelTextConfig = (Clay_TextElementConfig) {
    .textColor = { 0, 0, 0, 255},
    .fontId = 0,
    .fontSize = 16,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .wrapMode = CLAY_TEXT_WRAP_WORDS
};

const Clay_TextElementConfig InputTextTextConfig = (Clay_TextElementConfig) {
    .textColor = { 0, 0, 0, 255},
    .fontId = 0,
    .fontSize = 16,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .wrapMode = CLAY_TEXT_WRAP_WORDS
};

const Clay_ElementDeclaration MainButtonStyle = (Clay_ElementDeclaration) {
    MainButtonLayout,
    .backgroundColor = {191, 191, 191, 255},
    .cornerRadius = CLAY_CORNER_RADIUS(10)
};

/* Text */

const Clay_TextElementConfig WindowLabelText = (Clay_TextElementConfig) {
    .textColor = { 0, 0, 0, 255},
    .fontId = 0,
    .fontSize = 64,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .wrapMode = CLAY_TEXT_WRAP_NONE
};
