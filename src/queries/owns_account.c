#include "queries.h"
#include "stdbool.h"

bool owns_account(int acc_number, int user_id) {
  sqlite3_stmt *stmt;

  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    close_db_con();
    return false;
  }

  char *sql = "SELECT 1 FROM Records WHERE userId = ? AND accountNbr = ?";

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return false;
  }

  sqlite3_bind_int(stmt, 1, user_id);
  sqlite3_bind_int(stmt, 2, acc_number);

  if ((rc = sqlite3_step(stmt)) != SQLITE_ROW) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return false;
  }
  sqlite3_finalize(stmt);
  close_db_con();
  return true;
}
