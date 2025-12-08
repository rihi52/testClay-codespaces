#ifndef BUILD_ENCOUNTER_H
#define BUILD_ENCOUNTER_H

#include "clay.h"
#include "global.h"

#define BUILD_LIST_MAX  50

typedef struct BuildListMember {
    int initiative;
    char *name;
    int Quantity;
}BuildListMember;

extern Clay_String CreatureSearch;
extern Clay_String PlayerSearch;

void BuildEncounterWindow(AppState * state);
void PlayerBuildListCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData);

#endif /* BUILD_ENCOUNTER_H */
