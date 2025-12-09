#ifndef BUILD_ENCOUNTER_H
#define BUILD_ENCOUNTER_H

#include "clay.h"
#include "global.h"

/*========================================================================* 
 *  SECTION - Defines
 *========================================================================* 
 */

#define BUILD_LIST_MAX  50

/*========================================================================* 
 *  SECTION - Global structs
 *========================================================================* 
 */
typedef struct BuildListMember {
    int initiative;
    char *name;
    int Quantity;
}BuildListMember;

/*========================================================================* 
 *  SECTION - Global prototypes
 *========================================================================* 
 */
void BuildEncounterWindow(AppState * state);
void PlayerBuildListCallback(Clay_ElementId elementId, Clay_PointerData pointerData, void *userData);

#endif /* BUILD_ENCOUNTER_H */
