#include "header.h"
#include "queries/queries.h"
#include <stdio.h>

void deleteAccount(struct User u) {
  int option;
  struct Record r;

  char temp[100];

  system("clear");
  printf("\n\n\t\tEnter the account number you want to delete:  ");
  scanf("%s", temp);

  if (atm_atoi(temp) < 0) {
    printf("\n\t\tInvalid account number!");
    choose_exit_or_menu(u);
  }

  r.accountNbr = atm_atoi(temp);
  /* check if account exists */
  if (!owns_account(r.accountNbr, u.id)) {
    printf("\n\t\t Account number record not found !\n\n");
    choose_exit_or_menu(u);
  }

  printf("\n\n\t\t===================Delete Account====================\n");
  /* Display the account information  you want to delete*/
  account_info(r.accountNbr, u.id);
  /* Connect to the API for deleting the account record */
  if (delete_account(r.accountNbr, u.id) != SQLITE_OK) {
    printf("\n\t\tOops! An error occured\n\n");
    choose_exit_or_menu(u);
  }
  /* sucess message */
  printf("\n\n\t\t✔ Success deleting account!\n\n");
  choose_exit_or_menu(u);
}
