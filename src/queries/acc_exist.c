#include "queries.h"

//
bool check_acc_number(int accountNbr) {
  sqlite3_stmt *stmt;
  int rc = initialize_db_conn();

  char *sql = "SELECT count(*) FROM Records WHERE accountNbr = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return false;
  }

  sqlite3_bind_int(stmt, 1, accountNbr);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    // Tunery operators
    return count > 0 ? true : false; // Return true if account exists, 0 if not
  }

  sqlite3_finalize(stmt);
  log_error(sqlite3_errmsg(db));
  return false; // Error occurred
}
