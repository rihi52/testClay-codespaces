#ifndef STYLES_H
#define STYLES_H

#include "clay.h"
#include <stdio.h>

#define SIDEBAR_WIDTH_PX    300

Clay_ElementDeclaration MakeSidebarWindow(uint16_t width, uint16_t height, uint16_t padding, uint16_t childGap, uint16_t yAlign, uint16_t layoutDirection);
Clay_ElementDeclaration MakeParentWindowStyle(uint16_t padding, uint16_t childGap, uint16_t layoutDirection, Clay_Color COLOR);
Clay_ElementDeclaration MakeContentWindowStyle(uint16_t padding, uint16_t childGap, uint16_t yAlign, uint16_t layoutDirection, Clay_Color COLOR);
Clay_ElementDeclaration MakeSidebarStyle(uint16_t width, uint16_t height, uint16_t padding, uint16_t childGap, uint16_t yAlign, uint16_t layoutDirection, Clay_Color COLOR);
Clay_ElementDeclaration MakeButtonStyle(uint16_t width, uint16_t height, uint16_t padding, uint16_t childGap, Clay_Color COLOR);

/* Colors */
extern const Clay_Color COLOR_ORANGE;
extern const Clay_Color COLOR_BLUE;
extern const Clay_Color COLOR_LIGHT;
extern const Clay_Color COLOR_BLACK;
extern const Clay_Color COLOR_RED;
extern const Clay_Color COLOR_GREEN;
extern const Clay_Color COLOR_WHITE;
extern const Clay_Color COLOR_GRAY_BG;
extern const Clay_Color COLOR_BUTTON_GRAY;

/* Styles */

extern const Clay_LayoutConfig HeadLabelWindow;

extern const Clay_LayoutConfig SingleLineTextContainer;

extern const Clay_TextElementConfig WindowLabelText;

extern const Clay_TextElementConfig ButtonLabelTextConfig;

extern const Clay_TextElementConfig InputTextTextConfig;

#endif /* STYLES_H */