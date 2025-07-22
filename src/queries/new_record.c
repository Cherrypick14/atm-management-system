#include "../header.h"
#include "queries.h"
#include "sqlite3.h"

int new_record(struct Record r, char *name) {
  sqlite3 *db;
  int rc = sqlite3_open("atm.db", &db);
  sqlite3_stmt *stmt;

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    sqlite3_close(db);
    return rc;
  }
  int userId = get_user_id(name);

  char *sql = "INSERT INTO Records "
              "(userId,accountNbr,depositMonth,depositDay,depositYear,"
              "country,phone,amount,accountType) VALUES (?,?,?,?,?,?,?,?,?)";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    sqlite3_close(db);
    return rc;
  }

  sqlite3_bind_int(stmt, 1, userId);
  sqlite3_bind_int(stmt, 2, r.accountNbr);
  sqlite3_bind_int(stmt, 3, r.deposit.month);
  sqlite3_bind_int(stmt, 4, r.deposit.day);
  sqlite3_bind_int(stmt, 5, r.deposit.year);
  sqlite3_bind_text(stmt, 6, r.country, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 7, r.phone);
  sqlite3_bind_double(stmt, 8, r.amount);
  sqlite3_bind_text(stmt, 9, r.accountType, -1, SQLITE_STATIC);

  if ((rc = sqlite3_step(stmt)) != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    sqlite3_close(db);
    return rc;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return SQLITE_OK;
}
