#include "../clay.h"
#include "styles.h"
#include "global.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/*-------------------------------------------------------------------------------------------*
*                                 Function Prototypes                                        *
*--------------------------------------------------------------------------------------------*/
void ReturnToMainScreenCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
void StartEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
void BuildEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
void CreatureDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
void PlayerDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);

/*-------------------------------------------------------------------------------------------*
*                                     START COPY                                             *
*--------------------------------------------------------------------------------------------*/

int state = 0;

const int FONT_ID_BODY_16 = 0;
const int FONT_ID_BODY_32 = 0;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};

static const Uint32 FONT_ID = 0;

static const Clay_Color COLOR_ORANGE    = (Clay_Color) {225, 138, 50, 255};
static const Clay_Color COLOR_BLUE      = (Clay_Color) {111, 173, 162, 255};
static const Clay_Color COLOR_LIGHT     = (Clay_Color) {224, 215, 210, 255};
static const Clay_Color COLOR_BLACK     = (Clay_Color) {0, 0, 0, 255};
static const Clay_Color COLOR_RED       = (Clay_Color) {220, 0, 0, 255};
static const Clay_Color COLOR_GREEN     = (Clay_Color) {0, 220, 0, 255};

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

Clay_RenderCommandArray MainWindow(void)
{
    Clay_BeginLayout();

    Clay_Sizing layoutExpand = {
    .width = CLAY_SIZING_GROW(0),
    .height = CLAY_SIZING_GROW(0)
    };

    // Define one element that covers the whole screen
    CLAY(CLAY_ID("OuterContainer"), { ParentWindow, .backgroundColor = COLOR_WHITE}) {

        switch (state){
            case 0:
            /* Center container start */
            CLAY(CLAY_ID("HeadLabelContainer"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_WHITE}) {
                CLAY_TEXT(CLAY_STRING("GUIDNBATTER"), CLAY_TEXT_CONFIG(WindowLabel));
            };
            /* Start button start */
            CLAY(CLAY_ID("StartButton"), ButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Start Encounter"), CLAY_TEXT_CONFIG(ButtonLabel));
                Clay_OnHover(StartEncounterButtonCallback, (intptr_t)state);
            };

            /* Build button start */
            CLAY(CLAY_ID("BuildButton"), ButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Build Encounter"), CLAY_TEXT_CONFIG(ButtonLabel)); 
                Clay_OnHover(BuildEncounterButtonCallback, (intptr_t)state);
            };

            /* Creature button start */
            CLAY(CLAY_ID("CreatureDatabaseButton"), ButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Creature Database"), CLAY_TEXT_CONFIG(ButtonLabel));
                Clay_OnHover(CreatureDatabaseButtonCallback, (intptr_t)state);
            };

            /* Player button start */ 
            CLAY(CLAY_ID("PlayerDatabaseButton"), ButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Player Database"), CLAY_TEXT_CONFIG(ButtonLabel));
                Clay_OnHover(PlayerDatabaseButtonCallback, (intptr_t)state);
                
            };
            break;

        case 1:
            CLAY(CLAY_ID("StartEncounterHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_BLUE}) {
                CLAY_TEXT(CLAY_STRING("Start Encounter"), CLAY_TEXT_CONFIG(WindowLabel));
                Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)state);
            };
            break;
        
        case 2:
            CLAY(CLAY_ID("BuildEncounterHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_ORANGE}) {
                CLAY_TEXT(CLAY_STRING("Build Encounter"), CLAY_TEXT_CONFIG(WindowLabel));
                Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)state);
            };
            break;
        
        case 3:
            CLAY(CLAY_ID("CreatureDBHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_RED}) {
                CLAY_TEXT(CLAY_STRING("Creature DB"), CLAY_TEXT_CONFIG(WindowLabel));
                Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)state);
            };
            break;

        case 4:
            CLAY(CLAY_ID("PlayerDBHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_GREEN}) {
                CLAY_TEXT(CLAY_STRING("Player DB"), CLAY_TEXT_CONFIG(WindowLabel));
                Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)state);
            };
            break;

        default:
            break;
        }
    };

    return Clay_EndLayout();
}

/*-------------------------------------------------------------------------------------------*
*                                    Button Callbacks                                        *
*--------------------------------------------------------------------------------------------*/

void ReturnToMainScreenCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        state = MAIN_SCREEN;
    }
}

void StartEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        state = START_ENCOUNTER_SCREEN;
    }
}

void BuildEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        state = BUILD_ENCOUNTER_SCREEN;
    }
}

void CreatureDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    /* TODO: how should this work? changes only on mouse movement after clicking */
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        state = CREATURE_DB_SCREEN;
    }
}

void PlayerDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    /* TODO: how should this work? changes only on mouse movement after clicking */
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        state = PLAYER_DB_SCREEN;
    }
}