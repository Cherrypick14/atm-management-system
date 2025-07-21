#include "queries.h"
#include "string.h"
int account_type(int accountNumber) {

  sqlite3_stmt *stmt;
  int rc = initialize_db_conn();
  int res;

  char *sql = "SELECT accountType FROM Records WHERE accountNbr = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_bind_int(stmt, 1, accountNumber);

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    const char *accountType = (const char *)sqlite3_column_text(stmt, 0);
    if (strcmp(accountType, "saving") != 0 &&
        strcmp(accountType, "current") != 0) {
      res = -11;
    }
  }

  if (rc != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_finalize(stmt);
  log_error(sqlite3_errmsg(db));
  return res; // Er
}
