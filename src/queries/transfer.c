#include "queries.h"

int transfer_account(int userID, int accountNumber) {
  sqlite3_stmt *stmt;

  int rc = initialize_db_conn();

  if (rc != SQLITE_OK) {
    close_db_con();
    return SQLITE_ERROR;
  }
  //
  char *sql = "UPDATE Records SET userId = ? WHERE accountNbr = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_bind_int(stmt, 1, userID);
  sqlite3_bind_int(stmt, 2, accountNumber);

  if ((rc = sqlite3_step(stmt)) != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return SQLITE_ERROR;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return SQLITE_OK;
}
