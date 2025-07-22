#include "../header.h"
#include "queries.h"

int insert_user(char name[50], char password[50]) {
  sqlite3_stmt *stmt;
  int rc = initialize_db_conn();

  /*check for connection status */
  if (rc != SQLITE_OK) {
    close_db_con();
    return SQLITE_ERROR;
  }

  char *sql = "INSERT INTO Users (name,password) VALUES (?,?)"; /* sql query */
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0); /* preparing the sql query */

  /* checking the return status for the sql statement preparation */
  if (rc != SQLITE_OK) {
    close_db_con();
    return SQLITE_ERROR;
  }

  /* Bind the required values to the sqlite to prevent sql injection */
  sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

  /* Execute the sqlite query and check the return code|value */
  if ((rc = sqlite3_step(stmt)) != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return rc;
  }

  /* Finalize the sql statement execution and then close the database connection
   */
  sqlite3_finalize(stmt);
  close_db_con();
  return SQLITE_OK; /*  return value if the exection is sucessful*/
}
