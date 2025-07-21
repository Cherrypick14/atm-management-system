#include "queries.h"
#include "sqlite3.h"

int delete_account(int accountNbr, int user_id) {
  sqlite3_stmt *stmt;

  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    close_db_con();
    return SQLITE_ERROR;
  }

  char *sql = "DELETE FROM Records WHERE  accountNbr = ? AND userId = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_bind_int(stmt, 1, accountNbr);
  sqlite3_bind_int(stmt, 2, user_id);

  if ((rc = sqlite3_step(stmt)) != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    close_db_con();
    return SQLITE_ERROR;
  }
  sqlite3_finalize(stmt);
  close_db_con();
  return SQLITE_OK;
}
