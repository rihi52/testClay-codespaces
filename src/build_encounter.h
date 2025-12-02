#ifndef BUILD_ENCOUNTER_H
#define BUILD_ENCOUNTER_H

#include "clay.h"
#include "global.h"

typedef struct participant {
    char *name;
    int initiative;
    int initiativeSpot;
    int hp;
    bool isMalloc;
    struct part *next;
}participant;

void BuildEncounterWindow(AppState * state);

#endif /* BUILD_ENCOUNTER_H */