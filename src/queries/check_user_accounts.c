#include "../header.h"
#include "queries.h"
#include <stdio.h>

int check_user_accounts(int user_id) {
  sqlite3_stmt *stmt;
  int count = 0;

  /* Get a database connection*/
  int rc = initialize_db_conn();

  if (rc != SQLITE_OK) {
    close_db_con();
    return SQLITE_ERROR;
  }

  char *sql = "SELECT "
              "accountNbr,depositMonth,depositDay,depositYear,country,phone,"
              "amount,accountType FROM Records WHERE userId  = ?";

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_bind_int(stmt, 1, user_id);
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    count++;
    printf("\t\tAccount number: %d\n", sqlite3_column_int(stmt, 0));
    printf("\t\tDeposit date: %d/%d/%d\n", sqlite3_column_int(stmt, 1),
           sqlite3_column_int(stmt, 2), sqlite3_column_int(stmt, 3));
    printf("\t\tCountry: %s\n", sqlite3_column_text(stmt, 4));
    printf("\t\tPhone number: %d\n", sqlite3_column_int(stmt, 5));
    printf("\t\tAmount Deposited: %.2f\n", sqlite3_column_double(stmt, 6));
    printf("\t\tType of Account: %s\n", sqlite3_column_text(stmt, 7));
    printf("\t\t___________________________________\n\n");
  }

  if (count == 0) {
    printf("\n\t\tUser has no bank records.\n");
  }
  if (rc != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_finalize(stmt);
  close_db_con();
  return SQLITE_OK;
}
