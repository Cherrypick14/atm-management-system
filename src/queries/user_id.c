#include "queries.h"

int get_user_id(char *username) {
  sqlite3_stmt *stmt;
  int user_id;

  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    close_db_con();
    return -1;
  }

  char *sql = "SELECT id FROM Users WHERE name = ?";

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return -1;
  }

  sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
  if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    user_id = sqlite3_column_int(stmt, 0);
  } else {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return -1;
  }

  sqlite3_finalize(stmt);
  close_db_con();
  return user_id;
}
