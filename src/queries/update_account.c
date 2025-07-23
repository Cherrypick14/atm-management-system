#include "queries.h"

int update_country(int acc_number, char *country, int user_id) {
  sqlite3_stmt *stmt;

  /* get a connection to database */
  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    return SQLITE_ERROR;
  }

  /* sql statement to update the country from the records table */
  char *sql =
      "UPDATE Records SET country = ? WHERE accountNbr = ? and userId = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  /*binding the values to the sql query */
  sqlite3_bind_text(stmt, 1, country, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, acc_number);
  sqlite3_bind_int(stmt, 3, user_id);

  if ((rc = sqlite3_step(stmt)) != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_finalize(stmt);
  close_db_con();
  return SQLITE_OK;
}

int update_phone(int acc_number, int phone, int user_id) {
  sqlite3_stmt *stmt;

  int rc = initialize_db_conn();

  if (rc != SQLITE_OK) {
    close_db_con();
    return SQLITE_ERROR;
  }

  char *sql =
      "UPDATE Records SET phone = ? WHERE accountNbr = ? AND userId = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_bind_int(stmt, 1, phone);
  sqlite3_bind_int(stmt, 2, acc_number);
  sqlite3_bind_int(stmt, 3, user_id);

  if ((rc = sqlite3_step(stmt)) != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_finalize(stmt);
  close_db_con();
  return SQLITE_OK;
}
