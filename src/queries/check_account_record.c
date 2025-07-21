#include "../header.h"
#include "queries.h"
#include "sqlite3.h"
#include "stdio.h"

int check_account_record(int accountNumber, int user_id) {
  sqlite3_stmt *stmt;
  float interest;
  struct Record r;

  bool recordExist = false;

  /* sql statement */
  char *sql = "SELECT "
              "depositMonth,depositDay,depositYear,country,phone,amount,"
              "accountType FROM Records WHERE userId = ? AND accountNbr=? ";

  // get a connection
  int rc = initialize_db_conn();
  if (rc != SQLITE_OK) {
    close_db_con();
    return SQLITE_ERROR;
  }

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  //
  if (rc != SQLITE_OK) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return SQLITE_ERROR;
  }

  sqlite3_bind_int(stmt, 1, user_id);
  sqlite3_bind_int(stmt, 2, accountNumber);
  while ((rc = sqlite3_step(stmt) == SQLITE_ROW)) {
    recordExist = true;
    r.deposit.month = sqlite3_column_int(stmt, 0);
    r.deposit.day = sqlite3_column_int(stmt, 1);
    r.deposit.year = sqlite3_column_int(stmt, 2);
    snprintf(r.country, sizeof(r.country), "%s", sqlite3_column_text(stmt, 3));
    r.phone = sqlite3_column_int(stmt, 4);
    r.amount = sqlite3_column_double(stmt, 5);
    snprintf(r.accountType, sizeof(r.accountType), "%s",
             sqlite3_column_text(stmt, 6));

    printf("\n\n\t\tAccount number:\t%d\n", accountNumber);
    printf("\t\tDeposit date:\t%d/%d/%d\n", r.deposit.month, r.deposit.day,
           r.deposit.year);
    printf("\t\tCountry:\t%s\n", r.country);
    printf("\t\tPhone Number:\t%d\n", r.phone);
    printf("\t\tAmount deposited:\t%.2f\n", r.amount);
    printf("\t\tType of Account:\t%s\n", r.accountType);

  displayprofits:
    if (strcmp(r.accountType, "saving") == 0) {
      interest = r.amount * 0.07 * (1.0 / 12);
      printf("\n\n\t\tYou will get $%.2f as interest on day %d of every month.",
             interest,r.deposit.day);

    } else if (strcmp(r.accountType, "fixed01") == 0) {
      interest = r.amount * 0.04 * (12.0 / 12);
      printf("\n\n\t\tYou will get $%.2f as interest on %d/%d/%d.",
             interest,r.deposit.month,r.deposit.day,r.deposit.year+1);

    } else if (strcmp(r.accountType, "fixed02") == 0) {
      interest = r.amount * 0.05 * (24.0/ 12);
      printf("\n\n\t\tYou will get $%.2f as interest on %d/%d/%d",
             interest,r.deposit.month,r.deposit.day,r.deposit.year+2);

    } else if (strcmp(r.accountType, "fixed03") == 0) {
      interest = r.amount * 0.08 * (36.0/ 12);
      printf("\n\n\t\tYou will get $%.2f as interest on %d/%d/%d",
             interest,r.deposit.month,r.deposit.day,r.deposit.year+3);

    } else if (strcmp(r.accountType, "current") == 0) {
      printf("\n\n\t\tYou will not get interests because the account is of "
             "type current");
    }
  }
  if (recordExist != true) {
    printf("\n\n\t\t\x1b[38;2;255;131;131m ✗ Account %d not found.\n\x1b[0m",
           accountNumber);
  }
  if (rc != SQLITE_DONE) {
    log_error(sqlite3_errmsg(db));
    close_db_con();
    return rc;
  }
  sqlite3_finalize(stmt);
  close_db_con();
  return SQLITE_OK;
}
