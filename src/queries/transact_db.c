#include "queries.h"

double check_amount(int account_number) {
  /*Initialize amount*/
  double amount;

  sqlite3_stmt *stmt;

  /*sql query*/
  char *sql = "SELECT amount FROM Records WHERE accountNbr = ?";

  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return -1;
  }

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return -1;
  }

  //
  sqlite3_bind_int(stmt, 1, account_number);
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    amount = sqlite3_column_double(stmt, 0);
  }

  if (rc != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return -1;
  }
  sqlite3_finalize(stmt);
  close_db_con();
  return amount;
}

int withdraw_from_account(int account_number, double amount_to_deduct,
                          int user_id) {
  sqlite3_stmt *stmt;
  double accountBalance;

  double amountInAccount = check_amount(account_number);
  if ((amountInAccount - amount_to_deduct) < 0) {
    return -10;
  }
  //
  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    sqlite3_close(db);
  }
  //
  accountBalance = amountInAccount - amount_to_deduct;
  char *sql = "UPDATE Records SET amount = ? WHERE accountNbr = ?";

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    sqlite3_close(db);
    return SQLITE_ERROR;
  }

  sqlite3_bind_double(stmt, 1, accountBalance);
  sqlite3_bind_int(stmt, 2, account_number);
  sqlite3_bind_int(stmt, 3, user_id);

  //
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return SQLITE_OK;
}

int deposit_to_account(int account_number, double amount_to_deposit,
                       int user_id) {
  sqlite3_stmt *stmt;
  double accountBalance;

  double amountInAccount = check_amount(account_number);
  accountBalance = amountInAccount + amount_to_deposit;
  //
  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    sqlite3_close(db);
  }
  //
  char *sql =
      "UPDATE Records SET amount = ? WHERE accountNbr = ? AND userId = ?";

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_bind_int(stmt, 1, accountBalance);
  sqlite3_bind_int(stmt, 2, account_number);
  sqlite3_bind_int(stmt, 3, user_id);

  //
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return SQLITE_OK;
}
