#include "clay.h"
#include "styles.h"
#include "global.h"
#include "stdio.h"
#include "text_input.h"
#include "db_query.h"
#include "main_window.h"
#include "build_encounter.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>

char *BuildList[BUILD_LIST_MAX] = {0};

void BuildEncounterChain();
void PlayerBuildListCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData);
void AddToBuildChain(const char *ParticipantToAdd);

void BuildEncounterWindow(AppState * state) {
    CLAY(CLAY_ID("BuildWindowOuterContainer"), {LTRParentWindowLayoutConfig, .backgroundColor = COLOR_BLACK, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)} ) {
        /* Sidebar for option buttons */
        CLAY(CLAY_ID("BuildEncounterSidebar"), {
            SidebarLayoutConfig,
            .backgroundColor = COLOR_GRAY_BG,
            .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)
        }) {
            
            CLAY(CLAY_ID("BuildPlayerSidebarTop"), {
                SidebarTopLayoutConfig,
                .backgroundColor = COLOR_TRANSPARENT,
                .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX),
                .clip = {true, true, Clay_GetScrollOffset()}
            }) {

                CLAY(CLAY_ID("PlayerOne"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    Clay_OnHover(ReturnToMainScreenCallback, &WindowState);
                    CLAY_TEXT(CLAY_STRING("Finn"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                };
                CLAY(CLAY_ID("PlayerTwo"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    char *name = "Ravi";
                    Clay_String RaviName = { false, sizeof(name), "Ravi"};
                    SDL_Log("%s", RaviName.chars);
                    Clay_OnHover(PlayerBuildListCallback, &RaviName.chars );
                    CLAY_TEXT(CLAY_STRING("Ravi"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                };
                CLAY(CLAY_ID("PlayerThree"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    CLAY_TEXT(CLAY_STRING("Pax"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                };
                CLAY(CLAY_ID("PlayerFour"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    CLAY_TEXT(CLAY_STRING("Theon"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                };
            };
            
            CLAY(CLAY_ID("PlayerSidebarBottom"), SidebarBottomLayoutConfig) {
                CLAY(CLAY_ID("PlayerSearchTextBox"), {
                    SingleLineInputLayoutConfig,
                    .backgroundColor = (state->focusedId.id == CLAY_ID("PlayerSearchTextBox").id) ? COLOR_BLACK : COLOR_GRAY_BG,
                    .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_SM_PX),
                    .border = {
                        .width = CLAY_BORDER_ALL(INPUT_BORDER_WIDTH_PX),
                        .color = COLOR_WHITE
                    }
                }){
                    Clay_OnHover(FocusWindowCallback, state);
                    if (state->focusedId.id == CLAY_ID("PlayerSearchTextBox").id) {
                        /* Using dynamically changing char * SearchText */
                        CLAY_TEXT(TypedText, CLAY_TEXT_CONFIG(InputTextConfig));
                    }
                }

                CLAY(CLAY_ID("BuildPlayerSearchButton"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    // Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState); TODO: Fill this in with a sql search function
                    CLAY_TEXT(CLAY_STRING("Search"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                }; 
                CLAY(CLAY_ID("BuildEncounterAddButton"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    // Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState); TODO: Fill this in with a sql search function
                    CLAY_TEXT(CLAY_STRING("Add"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                };
            };
        };

        /* Main content containing monster lists and stats*/
        CLAY(CLAY_ID("BuildEncounterContentWindow"), {
            TTBBuildWindowLayoutConfig,
            .backgroundColor = COLOR_GRAY_BG,
            .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)
        }) {
            BuildEncounterChain();
        };
        CLAY(CLAY_ID("BuildEncounterCreatureSidebar"), {
            SidebarLayoutConfig,
            .backgroundColor = COLOR_GRAY_BG,
            .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)
        }) {
            
            CLAY(CLAY_ID("BuildCreatureSidebarTop"), {SidebarTopLayoutConfig,
                .backgroundColor = COLOR_TRANSPARENT,
                .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX),
                .clip = {true, true, Clay_GetScrollOffset()}
            }) /* Build Creature Sidebar Top contents*/ {
                // for (int i = 0; i < 30; i++) {
                //     MakeCreatureHeader(i, BUILD_ENCOUNTER_SCREEN);
                // }
            };
            
            CLAY(CLAY_ID("CreatureSidebarBottom"), SidebarBottomLayoutConfig) {
                CLAY(CLAY_ID("CreatureSearchTextBox"), {
                    SingleLineInputLayoutConfig,
                    .backgroundColor = (state->focusedId.id == CLAY_ID("CreatureSearchTextBox").id) ? COLOR_BLACK : COLOR_GRAY_BG,
                    .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_SM_PX),
                    .border = {
                        .width = CLAY_BORDER_ALL(INPUT_BORDER_WIDTH_PX),
                        .color = COLOR_WHITE
                    }
                }){
                    Clay_OnHover(FocusWindowCallback, state);
                    if (state->focusedId.id == CLAY_ID("CreatureSearchTextBox").id) {
                        /* Using dynamically changing char * SearchText */
                        CLAY_TEXT(TypedText, CLAY_TEXT_CONFIG(InputTextConfig));
                    }
                }

                CLAY(CLAY_ID("BuildCreatureSearchButton"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    // Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState); TODO: Fill this in with a sql search function
                    CLAY_TEXT(CLAY_STRING("Search"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                }; 
                CLAY(CLAY_ID("BuildEncounterCreatureAddButton"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                    // Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState); TODO: Fill this in with a sql search function
                    CLAY_TEXT(CLAY_STRING("Add"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                };                
            };
        };
    };
}

void BuildEncounterChain() {
    CLAY_AUTO_ID({
        BuildWindowRow,
        .backgroundColor = COLOR_GREEN,
        .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)
    }){

    }
}

void AddToBuildChain(const char *ParticipantToAdd) {
    for (int i = 0; i < BUILD_LIST_MAX; i++) {
        if (NULL == BuildList[i]) {
            SDL_strlcpy(BuildList[i], ParticipantToAdd, sizeof(ParticipantToAdd));
            SDL_Log("Added: %s", ParticipantToAdd);
            break;
        }
    }    
}

void PlayerBuildListCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        char *NameToAdd = (char *) userData;
        SDL_Log("Callback: %s", NameToAdd);
        AddToBuildChain(NameToAdd);
    }
}