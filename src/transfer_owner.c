#include "header.h"
#include "queries/queries.h"
#include <stdio.h>

void transferAccount(struct User u) {
  struct Record rc;
  struct User user;
  int option;
  char temp[100];

  printf("\n\t\tEnter the account number you want to transfer the ownership: ");
  scanf("%s", temp);

  if (atm_atoi(temp) < 0) {
    printf("\n\t\tInvalid account number!\n");
    choose_exit_or_menu(u);
  }

  rc.accountNbr = atm_atoi(temp);

  /* check if a user owns that account before making the transfer */
  if (!owns_account(rc.accountNbr, u.id)) {
    printf("\n\t\tInvalid account number!");
    choose_exit_or_menu(u);
  }

  // print the account details;
  printf("\n\t\t======== Transfering account ========");
  account_info(rc.accountNbr, u.id);

  printf(
      "\n\t\tWhich user you want to transfer the ownership to (user name):\t");
  scanf("%s", user.name);

  int user_id = get_user_id(user.name);
  if (user_id != -1) {
    transfer_account(user_id, rc.accountNbr);
    printf("\n\n\t\tSuccess");
    choose_exit_or_menu(u);
  }
  printf("\n\t\tUser doesn't exist!");
  choose_exit_or_menu(u);
}
