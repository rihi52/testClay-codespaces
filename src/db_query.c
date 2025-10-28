#include "db_query.h"

/*========================================================================*
 *  SECTION - External variables that cannot be defined in header files   *
 *========================================================================*
 */
sqlite3 * pGuidnbatterDB;

/*========================================================================*
 *  SECTION - Global function definitions                                 *
 *========================================================================*
 */
void DatabaseOpen(void) {

    int rc = sqlite3_open("../guidnbatter.db", &pGuidnbatterDB);
    if (rc)
    {
        /* Exit if the database can't be opened */
        SDL_Log("Can't open database: %s", sqlite3_errmsg(pGuidnbatterDB));
        return;
    }
    else
    {
        SDL_Log("Opened database successfully");
    }
    return;
}

void DatabaseClose(void) {
    sqlite3_close(pGuidnbatterDB);
}

const char * LookUpMonster(int monster_id) {
    
    static char name_buffer[128]; // Persistent buffer for returned name
    name_buffer[0] = '\0'; // Clear it

    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT name FROM monsters WHERE id = ?";

    int rc = sqlite3_prepare_v2(pGuidnbatterDB, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        SDL_Log("Failed to prepare statement: %s", sqlite3_errmsg(pGuidnbatterDB));
        return name_buffer;
    }

    sqlite3_bind_int(stmt, 1, monster_id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        const unsigned char *name = sqlite3_column_text(stmt, 0);
        if (name)
        {
            strncpy(name_buffer, (const char *)name, sizeof(name_buffer) - 1);
            name_buffer[sizeof(name_buffer) - 1] = '\0'; // Ensure null-termination
        }
    }
    else if (rc != SQLITE_DONE)
    {
        SDL_Log("Failed to execute statement: %s", sqlite3_errmsg(pGuidnbatterDB));
    }

    sqlite3_finalize(stmt);
    return name_buffer; // Safe static buffer
}