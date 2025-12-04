#ifndef BUILD_ENCOUNTER_H
#define BUILD_ENCOUNTER_H

#include "clay.h"
#include "global.h"

#define BUILD_LIST_MAX  50

typedef struct participant {
    char *name;
    int initiative;
    int initiativeSpot;
    int hp;
    bool isMalloc;
    struct participant *next;
}participant;

void BuildEncounterWindow(AppState * state);

#endif /* BUILD_ENCOUNTER_H */