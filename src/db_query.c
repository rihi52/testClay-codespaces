#include "db_query.h"

/*========================================================================*
 *  SECTION - External variables that cannot be defined in header files   *
 *========================================================================*
 */
sqlite3 * pCreatureDatabase;

/*========================================================================*
 *  SECTION - Global function definitions                                 *
 *========================================================================*
 */
void DatabaseOpen(void) {

    int rc = sqlite3_open("creatures.db", &pMonsterDb);
    if (rc)
    {
        /* Exit if the database can't be opened */
        SDL_Log("Can't open database: %s", sqlite3_errmsg(pMonsterDb));
        return;
    }
    else
    {
        SDL_Log("Opened database successfully");
    }
    return;
}