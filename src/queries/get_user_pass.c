#include "queries.h"
#include <string.h>

char *get_user_pass(char name[50]) {
  sqlite3_stmt *stmt;
  char *password;
  /* get database connection */
  int rc = initialize_db_conn();

  if (rc != SQLITE_OK) {
    return "SQLITE_ERROR";
  }

  char *sql = "SELECT PASSWORD FROM Users WHERE name = ?";

  /* Prepare the sql statement */
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return "SQLITE_ERROR";
  }

  sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
  rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    password = strdup((char *)sqlite3_column_text(stmt, 0));
  } else if (rc == SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    password = strdup("usernotfound");
  } else {
    log_error(sqlite3_errmsg(db));
    close_db_con();
  }

  sqlite3_finalize(stmt);
  close_db_con();
  return password;
}
