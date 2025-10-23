#include "clay.h"
#include "styles.h"
#include "global.h"

/*========================================================================* 
 *  SECTION - Clay_Color definitions
 *========================================================================* 
 */
const Clay_Color COLOR_ORANGE       = (Clay_Color) {225, 138, 50, 255};
const Clay_Color COLOR_BLUE         = (Clay_Color) {111, 173, 162, 255};
const Clay_Color COLOR_LIGHT        = (Clay_Color) {224, 215, 210, 255};
const Clay_Color COLOR_BLACK        = (Clay_Color) {0, 0, 0, 255};
const Clay_Color COLOR_RED          = (Clay_Color) {220, 0, 0, 255};
const Clay_Color COLOR_GREEN        = (Clay_Color) {0, 220, 0, 255};
const Clay_Color COLOR_WHITE        = (Clay_Color) { 255, 255, 255, 255};
const Clay_Color COLOR_GRAY_BG      = (Clay_Color) {20, 20, 20, 255};
const Clay_Color COLOR_TRANSPARENT  = (Clay_Color) {0, 0, 0, 0};
const Clay_Color COLOR_BUTTON_GRAY  = (Clay_Color) {70, 70, 70, 255};

/*========================================================================* 
 *  SECTION - Global Functions
 *========================================================================* 
 */

/* This function returns a Clay_ElementDeclaration struct used for styling a Sidebar
 * It assumes CLAY_SIZING_FIXED(width), CLAY_SIZING_GROW(0, height), and CLAY_ALING_X_CENTER */
Clay_ElementDeclaration MakeSidebarWindow(uint16_t width, uint16_t height, uint16_t padding, uint16_t childGap, uint16_t yAlign, uint16_t layoutDirection) {

    Clay_LayoutConfig SidebarWindowConfig = {
    .sizing = { CLAY_SIZING_FIXED(width), CLAY_SIZING_GROW(0, (height)) },
    .padding = { padding, padding, padding, padding},
    .childGap = childGap,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, yAlign },
    .layoutDirection = layoutDirection
    };

    return (Clay_ElementDeclaration) {
        .layout = SidebarWindowConfig,
        .backgroundColor = {0, 0, 0, 0},
        .cornerRadius = CLAY_CORNER_RADIUS(10)
    };
}

/* This function returns a Clay_ElementDeclaration struct used for styling a Parent Window
 * It assumes CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0), CLAY_ALING_X_CENTER, and CLAY_ALIGN_Y_CENTER */
Clay_ElementDeclaration MakeParentWindowStyle(uint16_t padding, uint16_t childGap, uint16_t layoutDirection, Clay_Color COLOR) {

    Clay_LayoutConfig ParentWindowConfig = {
    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
    .padding = { padding, padding, padding, padding},
    .childGap = childGap,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = layoutDirection
    };

    return (Clay_ElementDeclaration) {
        .layout = ParentWindowConfig,
        .backgroundColor = COLOR,
        .cornerRadius = CLAY_CORNER_RADIUS(10)
    };
}

/* This function returns a Clay_ElementDeclaration struct used for styling a Content Window
 * It assumes CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0), CLAY_ALING_X_CENTER */
Clay_ElementDeclaration MakeContentWindowStyle(uint16_t padding, uint16_t childGap, uint16_t yAlign, uint16_t layoutDirection, Clay_Color COLOR) {

    Clay_LayoutConfig ContentWindowConfig = {
    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
    .padding = { padding, padding, padding, padding},
    .childGap = childGap,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, yAlign },
    .layoutDirection = layoutDirection
    };

    return (Clay_ElementDeclaration) {
        .layout = ContentWindowConfig,
        .backgroundColor = COLOR,
        .cornerRadius = CLAY_CORNER_RADIUS(10)
    };
}

/* This function returns a Clay_ElementDeclaration struct used for styling a Sidebar
 * It assumes CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0), CLAY_ALING_X_CENTER, and CLAY_ALIGN_Y_CENTER */
Clay_ElementDeclaration MakeSidebarStyle(uint16_t width, uint16_t height, uint16_t padding, uint16_t childGap, uint16_t yAlign, uint16_t layoutDirection, Clay_Color COLOR) {

    Clay_LayoutConfig ContentWindowConfig = {
    .sizing = { CLAY_SIZING_FIXED(width), CLAY_SIZING_GROW(0, height) },
    .padding = { padding, padding, padding, padding},
    .childGap = childGap,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = layoutDirection
    };

    return (Clay_ElementDeclaration) {
        .layout = ContentWindowConfig,
        .backgroundColor = COLOR,
        .cornerRadius = CLAY_CORNER_RADIUS(10)
    };
}

/* This function returns a Clay_ElementDeclaration struct used for styling a Sidebar
 * It assumes CLAY_SIZING_FIXED(width), CLAY_SIZING_FIXED(height), CLAY_ALING_X_CENTER, CLAY_ALIGN_Y_CENTER, and CLAY_TOP_TO_BOTTOM */
Clay_ElementDeclaration MakeButtonStyle(uint16_t width, uint16_t height, uint16_t padding, uint16_t childGap, Clay_Color COLOR) {

    Clay_LayoutConfig ContentWindowConfig = {
    .sizing = { CLAY_SIZING_FIXED(width), CLAY_SIZING_FIXED(height) },
    .padding = { padding, padding, padding, padding},
    .childGap = childGap,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = CLAY_TOP_TO_BOTTOM
    };

    return (Clay_ElementDeclaration) {
        .layout = ContentWindowConfig,
        .backgroundColor = COLOR,
        .cornerRadius = CLAY_CORNER_RADIUS(10)
    };
}

/*========================================================================* 
 *  SECTION - Constant Styles
 *========================================================================* 
 */

const Clay_LayoutConfig HeadLabelWindow = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_FIXED(500), CLAY_SIZING_FIXED(100) },
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

const Clay_TextElementConfig ButtonLabelTextConfig = (Clay_TextElementConfig) {
    .textColor = COLOR_WHITE,
    .fontId = 0,
    .fontSize = 16,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .wrapMode = CLAY_TEXT_WRAP_WORDS
};

const Clay_TextElementConfig InputTextTextConfig = (Clay_TextElementConfig) {
    .textColor = COLOR_WHITE,
    .fontId = 0,
    .fontSize = 16,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .wrapMode = CLAY_TEXT_WRAP_WORDS
};

/* Text */

const Clay_TextElementConfig WindowLabelText = (Clay_TextElementConfig) {
    .textColor = COLOR_WHITE,
    .fontId = 0,
    .fontSize = 64,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .wrapMode = CLAY_TEXT_WRAP_NONE
};