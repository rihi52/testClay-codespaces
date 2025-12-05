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

char BuildList[BUILD_LIST_MAX][64] = {0};
Clay_String RaviName = {0};

void BuildEncounterChain(int position);
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
                    RaviName = CLAY_STRING("Ravi");
                    Clay_OnHover(PlayerBuildListCallback, &RaviName );
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
                // CLAY(CLAY_ID("BuildEncounterAddButton"), {MainScreenButtonLayoutConfig, .backgroundColor = COLOR_BUTTON_GRAY, .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)}) {
                //     // Clay_OnHover(ReturnToMainScreenCallback, (intptr_t)WindowState); TODO: Fill this in with a sql search function
                //     CLAY_TEXT(CLAY_STRING("Add"), CLAY_TEXT_CONFIG(ButtonTextConfig));
                // };
            };
        };

        /* Main content containing monster lists and stats*/
        CLAY(CLAY_ID("BuildEncounterContentWindow"), {
            TTBBuildWindowLayoutConfig,
            .backgroundColor = COLOR_GRAY_BG,
            .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX),
            .clip = {true, true, Clay_GetScrollOffset()}
        }) {
            CLAY(CLAY_ID("BuildListHeader"), {
                BuildWindowRow
            }) {
                CLAY_AUTO_ID(BuildWindowInitiativeHeader){
                    CLAY_TEXT(CLAY_STRING("Initiative"), CLAY_TEXT_CONFIG(StatPageTextConfig));
                }
                CLAY_AUTO_ID(BuildWindowDescriptionHeader){
                    CLAY_TEXT(CLAY_STRING("Description"), CLAY_TEXT_CONFIG(StatPageTextConfig));
                }
                CLAY_AUTO_ID(BuildWindowQuantityHeader){
                    CLAY_TEXT(CLAY_STRING("Quantity"), CLAY_TEXT_CONFIG(StatPageTextConfig));
                }
            }
            for (int i = 0; i < BUILD_LIST_MAX; i++) {
            if ('\0' != BuildList[i][0]) {
                BuildEncounterChain(i);
            }
    } 
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
                    Clay_OnHover(FocusWindowCallback, gAppState);
                    if (gAppState->focusedId.id == CLAY_ID("CreatureSearchTextBox").id) {
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

void BuildEncounterChain(int position) {
    CLAY_AUTO_ID({
        BuildWindowRow,
        .backgroundColor = COLOR_GREEN,
        .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_LG_PX)
    }){
        CLAY(CLAY_IDI("BuildListPosition", position), {
            BuildInitiativeQuantityLayoutConfig,
            .backgroundColor = (gAppState->focusedId.id == CLAY_IDI("BuildListPosition", position).id) ? COLOR_BLACK : COLOR_GRAY_BG,
            .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_SM_PX),
            .border = {
                .width = CLAY_BORDER_ALL(INPUT_BORDER_WIDTH_PX),
                .color = COLOR_WHITE
            }
        }){
            Clay_OnHover(FocusWindowCallback, gAppState);
            if (gAppState->focusedId.id == CLAY_IDI("BuildListPosition", position).id) {
                /* Using dynamically changing char * SearchText */
                CLAY_TEXT(TypedText, CLAY_TEXT_CONFIG(InputTextConfig));
            }
        }
        CLAY(CLAY_IDI("BuildListInitiative", position), {BuildWindowDescriptionHeader}){
            if ('\0' != BuildList[0][0]) {
                Clay_String NameAdd = MakeClayString(BuildList[0]);
                CLAY_TEXT(NameAdd, CLAY_TEXT_CONFIG(StatPageTextConfig));
            }
        }
        CLAY(CLAY_IDI("BuildListInitiative", position), {
            BuildInitiativeQuantityLayoutConfig,
            .backgroundColor = (gAppState->focusedId.id == CLAY_IDI("BuildListInitiative", position).id) ? COLOR_BLACK : COLOR_GRAY_BG,
            .cornerRadius = CLAY_CORNER_RADIUS(GLOBAL_RADIUS_SM_PX),
            .border = {
                .width = CLAY_BORDER_ALL(INPUT_BORDER_WIDTH_PX),
                .color = COLOR_WHITE
            }
        }){
            Clay_OnHover(FocusWindowCallback, gAppState);
            if (gAppState->focusedId.id == CLAY_ID("BuildListInitiative").id) {
                /* Using dynamically changing char * SearchText */
                CLAY_TEXT(TypedText, CLAY_TEXT_CONFIG(InputTextConfig));
            }
        }
    }
}

void AddToBuildChain(const char *ParticipantToAdd) {
    for (int i = 0; i < BUILD_LIST_MAX; i++) {
        if ('\0' == BuildList[i][0]) {
            SDL_strlcpy(BuildList[i], ParticipantToAdd, 64);
            SDL_Log("Added: %s", BuildList[i]);
            break;
        }
    }    
}

void PlayerBuildListCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        Clay_String *NameToAdd = (Clay_String *) userData;
        SDL_Log("Callback: %s", NameToAdd->chars);
        AddToBuildChain(NameToAdd->chars);
    }
}
