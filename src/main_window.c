#include "main_window.h"
#include "clay.h"
#include "styles.h"
#include "global.h"
#include "stdio.h"
#include "text_input.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>

/*========================================================================* 
 *  SECTION - Local prototypes
 *========================================================================* 
 */
static void ReturnToMainScreenCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
static void StartEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
static void BuildEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
static void CreatureDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);
static void PlayerDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData);

void CreatureDatabaseWindow(AppState * state);
void PlayerDatabaseWindow(void);

/*========================================================================* 
 *  SECTION - Layouts 
 *========================================================================* 
 */

Clay_RenderCommandArray MainWindow(AppState * state)
{
    Clay_BeginLayout();

    Clay_Sizing layoutExpand = {
    .width = CLAY_SIZING_GROW(0),
    .height = CLAY_SIZING_GROW(0)
    };

    // Define one element that covers the whole screen
    CLAY(CLAY_ID("OuterContainer"), { TTBParentWindow, .backgroundColor = COLOR_WHITE}) {

        switch (WindowState){
            case 0:
            /* Center container start */
            CLAY(CLAY_ID("HeadLabelContainer"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_WHITE}) {
                CLAY_TEXT(CLAY_STRING("GUIDNBATTER"), CLAY_TEXT_CONFIG(WindowLabelText));
            };
            /* Start button start */
            CLAY(CLAY_ID("StartButton"), MainButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Start Encounter"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig));
                Clay_OnHover(StartEncounterButtonCallback, (intptr_t)WindowState);
            };

            /* Build button start */
            CLAY(CLAY_ID("BuildButton"), MainButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Build Encounter"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig)); 
                Clay_OnHover(BuildEncounterButtonCallback, (intptr_t)WindowState);
            };

            /* Creature button start */
            CLAY(CLAY_ID("CreatureDatabaseButton"), MainButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Creature Database"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig));
                Clay_OnHover(CreatureDatabaseButtonCallback, (intptr_t)WindowState);
            };

            /* Player button start */ 
            CLAY(CLAY_ID("PlayerDatabaseButton"), MainButtonStyle) {
                CLAY_TEXT(CLAY_STRING("Player Database"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig));
                Clay_OnHover(PlayerDatabaseButtonCallback, (intptr_t)WindowState);
                
            };
            break;

        case START_ENCOUNTER_SCREEN:
            CLAY(CLAY_ID("StartEncounterHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_BLUE}) {
                CLAY_TEXT(CLAY_STRING("Start Encounter"), CLAY_TEXT_CONFIG(WindowLabelText));
                Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState);
            };
            break;
        
        case BUILD_ENCOUNTER_SCREEN:
            CLAY(CLAY_ID("BuildEncounterHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_ORANGE}) {
                CLAY_TEXT(CLAY_STRING("Build Encounter"), CLAY_TEXT_CONFIG(WindowLabelText));
                Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState);
            };
            break;
        
        case CREATURE_DB_SCREEN:
            CreatureDatabaseWindow(state);
            break;

        case PLAYER_DB_SCREEN:
            PlayerDatabaseWindow();            
            break;

        default:
            break;
        }
    };

    return Clay_EndLayout();
}

void CreatureDatabaseWindow(AppState * state) {
    /* Creature database window*/
    CLAY(CLAY_ID("CreatureDBOuterContainer"), { LTRParentWindow, .backgroundColor = COLOR_WHITE}) {
        
        /* Sidebar for option buttons */
        CLAY(CLAY_ID("CreatureDBSidebar"), SidebarWindowStyle) {
            Clay_ElementData ParentSidebar = Clay_GetElementData(CLAY_ID("CreatureDBSidebar"));
            
            CLAY(CLAY_ID("SidebarTop"), {.layout = {.sizing = CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(ParentSidebar.boundingBox.width)}}){
                CLAY(CLAY_ID("CreatureDBHomeButton"), MainButtonStyle) {
                    Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState);
                    CLAY_TEXT(CLAY_STRING("Return Home"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig));
                };
                CLAY(CLAY_ID("CreatureDBAddButton"), MainButtonStyle) {
                    CLAY_TEXT(CLAY_STRING("Add"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig));
                };
                CLAY(CLAY_ID("CreatureDBRemoveButton"), MainButtonStyle) {
                    CLAY_TEXT(CLAY_STRING("Remove"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig));
                };
                CLAY(CLAY_ID("CreatureDBEditButton"), MainButtonStyle) {
                    CLAY_TEXT(CLAY_STRING("Edit"), CLAY_TEXT_CONFIG(ButtonLabelTextConfig));
                };
            };
        };

        /* Main content containing monster lists and stats*/
        CLAY(CLAY_ID("CreatureDBContentWindow"), ContentWindowStyle){
            CLAY(CLAY_ID("CreatureDBHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_RED}) {
                CLAY_TEXT(CLAY_STRING("Creature DB"), CLAY_TEXT_CONFIG(WindowLabelText));
            };
            CLAY(CLAY_ID("TextBox"), {SingleLineTextContainer, .backgroundColor = COLOR_WHITE}){

                /* Create char* and set equal to the overall buffer that reads keyboard input */
                char * SearchText = &TextBuffer[0];
                /* Custom clay_string to allow for a dynamically changing char* */
                Clay_String SomeTextMaybe = {.isStaticallyAllocated = true, .length = SDL_strlen(SearchText), .chars = SearchText};
                /* Using dynamically changing char * SearchText */
                CLAY_TEXT(SomeTextMaybe, CLAY_TEXT_CONFIG(InputTextTextConfig));
                             
            };            
        }
    }
}

void PlayerDatabaseWindow(void) {
    CLAY(CLAY_ID("PlayerDBOuterContainer"), { LTRParentWindow, .backgroundColor = COLOR_WHITE}) {
        CLAY(CLAY_ID("CreatureDBLeftPane"), {SidebarWindow, .backgroundColor = COLOR_BLUE});
        CLAY(CLAY_ID("PlayerDBHeader"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_GREEN}) {
            CLAY_TEXT(CLAY_STRING("Player DB"), CLAY_TEXT_CONFIG(WindowLabelText));
            Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState);
        };
    }
}

/*-------------------------------------------------------------------------------------------*
*                                    Button Callbacks                                        *
*--------------------------------------------------------------------------------------------*/

static void ReturnToMainScreenCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        SDL_memset(TextBuffer, 0, sizeof(TextBuffer));
        WindowState = MAIN_SCREEN;
    }
}

static void StartEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        WindowState = START_ENCOUNTER_SCREEN;
    }
}

static void BuildEncounterButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        WindowState = BUILD_ENCOUNTER_SCREEN;
    }
}

static void CreatureDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    /* TODO: how should this work? changes only on mouse movement after clicking */
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        WindowState = CREATURE_DB_SCREEN;
    }
}

static void PlayerDatabaseButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    int check = (int) userData;
    /* TODO: how should this work? changes only on mouse movement after clicking */
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        WindowState = PLAYER_DB_SCREEN;
    }
}