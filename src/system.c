#include "header.h"
#include "queries/sqlite3.h"
#include "stdbool.h"
#include <stdio.h>

bool valid_date(int month, int day, int year)
{
  if (month < 1 || month > 12)
  {
    return false;
  }
  if (day < 1 || day > 30)
  {
    return false;
  }

  if (year < 1900 || year > 2100)
  {
    return false;
  }
  return true;
}

void createNewAcc(struct User u)
{
  struct Record r;
  struct Record cr;
  char userName[50];

  //
  char temp_acc[100]=""; 
  char temp_phone[100];

noAccount:
  system("clear");
  printf("\t\t\t===== New record =====\n");

  printf("\n\t\tEnter today's date(mm/dd/yyyy): ");
  scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
  if (!valid_date(r.deposit.month, r.deposit.day, r.deposit.year))
  {
    goto noAccount;
  }
  printf("\n\t\tEnter the account number: ");
  scanf("%s", temp_acc);
  //check for valid account number
  if ((r.accountNbr = atm_atoi(temp_acc)) == -1){
    printf("\n\t\tInvalid input\n");
    choose_exit_or_menu(u);
  }
  printf("\n\t\tEnter the country: ");
  read_string(r.country, sizeof(r.country));

  printf("\n\t\tEnter the phone number: ");
  scanf("%s", temp_phone);
  if ((r.phone = atm_atoi(temp_phone)) == -1){
    printf("\n\t\tInvalid phone number\n\n");
    choose_exit_or_menu(u);
  }

  printf("\n\t\tEnter amount to deposit: $");
  if (!parseFloat(&r.amount))
  {
    printf("\n\t\tInvalid input.\n\n");
    choose_exit_or_menu(u);
  }
  printf("\n\t\tChoose the type of account:\n\t\t\t-> saving\n\t\t\t-> current\n\t\t\t-> "
         "fixed01(for 1 year)\n\t\t\t-> fixed02(for 2 years)\n\t\t\t-> fixed03(for 3 "
         "years)\n\n\t\t\tEnter your choice: ");

  read_string(r.accountType, sizeof(r.accountType));
  if (strcmp(r.accountType, "fixed01") != 0 &&
      strcmp(r.accountType, "fixed02") != 0 &&
      strcmp(r.accountType, "fixed03") != 0 &&
      strcmp(r.accountType, "saving") != 0 &&
      strcmp(r.accountType, "current") != 0)
  {
    printf("Invalid account type!.\n");
    choose_exit_or_menu(u);
  }

  int result = new_record(r, u.name);
  if (result == SQLITE_CONSTRAINT)
  {
    printf("✖ This Account already exists for this user\n\n");
    goto noAccount;
  }
  printf("\n\t\t✔ Success!\n\n");
  choose_exit_or_menu(u);
}
