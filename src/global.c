#include "clay.h"
#include "global.h"
#include "db_query.h"
#include "styles.h"

/*========================================================================* 
 *  SECTION - Local prototypes
 *========================================================================* 
 */
static void ClearTextBoxes();

/*========================================================================* 
 *  SECTION - extern variables
 *========================================================================* 
 */
int WindowState = 0;

char TextBuffer[MAX_TEXT] = {0};

const int FONT_ID_BODY_16 = 0;
const int FONT_ID_BODY_32 = 0;

int WindowWidth = 0;
int WindowHeight = 0;
uint16_t TotalCreatures = 0;

float ScrollOffset = 0;

bool MouseDown;

TextBox BuildCreatureSearch;
TextBox BuildPlayerSearch;
TextBox DBCreatureSearch;
TextBox DBPlayerSearch;

Clay_String StatName = {0};
Clay_String StatSize = {0};
Clay_String StatType = {0};
Clay_String StatAC = {0};
Clay_String StatHP = {0};
Clay_String StatSpeed = {0};
Clay_String StatStr = {0};
Clay_String StatDex = {0};
Clay_String StatCon = {0};
Clay_String StatInt = {0};
Clay_String StatWis = {0};
Clay_String StatCha = {0};

Clay_String StatSaves = {0};
Clay_String StatSkills = {0};
Clay_String StatSenses = {0};
Clay_String StatLanguages = {0};
Clay_String StatCR = {0};

Clay_String StatRacial1 = {0};
Clay_String StatRacial2 = {0};
Clay_String StatRacial3 = {0};

Clay_String StatAction1 = {0};
Clay_String StatAction2 = {0};
Clay_String StatAction3 = {0};
Clay_String StatAction4 = {0};

/*========================================================================* 
 *  SECTION - Global functions
 *========================================================================* 
 */

 /* Helpers */
void ModifyTextBoxText(TextBox * TextToModify, uint32_t CopyOrWrite) {
    
    
    if (COPY_TEXT == CopyOrWrite) {
        memset(TextBuffer, 0, sizeof(TextBuffer));
        SDL_strlcpy(TextBuffer, TextToModify->TextBoxBuffer, MAX_TEXT);
    }
    else {
        SDL_strlcpy(TextToModify->TextBoxBuffer, TextBuffer, sizeof(TextBuffer));
        
    }
    TextToModify->StringToDisplay.length = SDL_strlen(TextToModify->TextBoxBuffer);
}

void FocusAndWriteTextBox(Clay_ElementId IdToFocus, uint32_t CurrentFocus, TextBox * TextToModify) {
    if (gAppState->focusedId.id == IdToFocus.id) {
        if(PreviousFocusId != CurrentFocus) {
            ModifyTextBoxText(TextToModify, COPY_TEXT);
        }
        else {
            ModifyTextBoxText(TextToModify, WRITE_TEXT);
        }
    }
    CLAY_TEXT(TextToModify->StringToDisplay, CLAY_TEXT_CONFIG(InputTextConfig));
}

void InitializeTextBoxes() {
    SDL_memset(BuildCreatureSearch.TextBoxBuffer, 0, sizeof(BuildCreatureSearch.TextBoxBuffer));
    BuildCreatureSearch.StringToDisplay.chars = BuildCreatureSearch.TextBoxBuffer;
    BuildCreatureSearch.StringToDisplay.length = 0;
    BuildCreatureSearch.StringToDisplay.isStaticallyAllocated = false;

    SDL_memset(BuildPlayerSearch.TextBoxBuffer, 0, sizeof(BuildPlayerSearch.TextBoxBuffer));
    BuildPlayerSearch.StringToDisplay.chars = BuildPlayerSearch.TextBoxBuffer;
    BuildPlayerSearch.StringToDisplay.length = 0;
    BuildPlayerSearch.StringToDisplay.isStaticallyAllocated = false;

    SDL_memset(DBCreatureSearch.TextBoxBuffer, 0, sizeof(DBCreatureSearch.TextBoxBuffer));
    DBCreatureSearch.StringToDisplay.chars = DBCreatureSearch.TextBoxBuffer;
    DBCreatureSearch.StringToDisplay.length = 0;
    DBCreatureSearch.StringToDisplay.isStaticallyAllocated = false;

    SDL_memset(DBPlayerSearch.TextBoxBuffer, 0, sizeof(DBPlayerSearch.TextBoxBuffer));
    DBPlayerSearch.StringToDisplay.chars = DBPlayerSearch.TextBoxBuffer;
    DBPlayerSearch.StringToDisplay.length = 0;
    DBPlayerSearch.StringToDisplay.isStaticallyAllocated = false;
}

static void ClearTextBoxes() {
    SDL_memset(TextBuffer, 0, sizeof(TextBuffer));

    SDL_memset(BuildCreatureSearch.TextBoxBuffer, 0, sizeof(BuildCreatureSearch.TextBoxBuffer));
    BuildCreatureSearch.StringToDisplay.length = 0;

    SDL_memset(BuildPlayerSearch.TextBoxBuffer, 0, sizeof(BuildPlayerSearch.TextBoxBuffer));
    BuildPlayerSearch.StringToDisplay.length = 0;

    SDL_memset(DBCreatureSearch.TextBoxBuffer, 0, sizeof(DBCreatureSearch.TextBoxBuffer));
    DBCreatureSearch.StringToDisplay.length = 0;

    SDL_memset(DBPlayerSearch.TextBoxBuffer, 0, sizeof(DBPlayerSearch.TextBoxBuffer));
    DBPlayerSearch.StringToDisplay.length = 0;
}

/* Callbacks*/

void FocusWindowCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void * userData) {
    AppState *state = userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        gAppState->focusedId = CLAY_ID("NULL");
        gAppState->focusedId = elementId;
        SDL_Log("FocusCallback");
    }
}

void ReturnToMainScreenCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData) {
    int * check = (int *) userData;
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        gAppState->focusedId = CLAY_ID("NULL");
        ClearTextBoxes();
        ScrollOffset = 0;
        WindowState = MAIN_SCREEN;
        // WindowState = ADD_STAT_SCREEN;
    }
}

void SearchButtonCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData) {
    // if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
    //     char * SearchText = &TextBuffer[0];
    //     SearchCreatureNames(SearchText);
    // }
}