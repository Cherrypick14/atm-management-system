#include "header.h"
#include "queries/queries.h"
#include <stdio.h>

void checkAccount(struct User u) {
  struct Record r;
  char temp[100];
  system("clear");
  printf("\n\t\tEnter your account number: ");
  scanf("%s", temp);
  //
  // checking for only integer account number
  if (atm_atoi(temp) == -1) {
    printf("\nInvalid account number.");
  }
  r.accountNbr = atm_atoi(temp);

  int user_id = get_user_id(u.name);
  if (check_account_record(r.accountNbr, user_id) != SQLITE_OK) {
    printf("\n\t\tOops, an error occured !\n");
    choose_exit_or_menu(u);
  }

  choose_exit_or_menu(u);
}
