#include "header.h"
#include "queries/queries.h"
#include <stdio.h>
#include <string.h>

void makeTransaction(struct User u) {
  struct Record r;
  char temp_acc[100];
  char temp_choice[2];

  printf("\n\t\tEnter the account number of the customer: ");
  scanf("%s", temp_acc);

  /* check for valid integer */
  if (atm_atoi(temp_acc) < 0) {
    printf("\n\t\tInvalid account number.\n");
    choose_exit_or_menu(u);
  }
  r.accountNbr = atm_atoi(temp_acc);

  /* check if user truly owns an account */
  if (!owns_account(r.accountNbr, u.id)) {
    printf("\n\t\tAccount number doesn't exist!\n");
    choose_exit_or_menu(u);
  }

  /* check if account number exists */
  if (!check_acc_number(r.accountNbr)) {
    printf("\n\t\tAccount doesn't exist.\n");
    choose_exit_or_menu(u);
  }

  // check account type
  if ( account_type(r.accountNbr) == -11) {
    printf("\n\t\tYou cannot deposit or withdraw in fixed accounts\n\n");
    choose_exit_or_menu(u);
  }

  printf("\n\t\tDo you want to:\n\n\t\t\t1->Withdraw\n\t\t\t2->Deposit\n");
  scanf("%s", temp_choice);

  /* validating input */
  if (atm_atoi(temp_choice) < 1 || atm_atoi(temp_choice) > 2) {
    printf("\n\t\tInvalid choice.\n");
    choose_exit_or_menu(u);
  }

  int choice = atm_atoi(temp_choice);

  if (choice == 1) {
    printf("\n\t\tEnter the amount you want to withdraw: ");
    if (!parseFloat(&r.amount)) {
      printf("\n\t\tInvalid Input\n\n");
      choose_exit_or_menu(u);
    }

    if (r.amount < 1) {
      printf("\n\t\tThe withdrawal amount must be greater than 0.\n");
      choose_exit_or_menu(u);
    }

    if (withdraw_from_account(r.accountNbr, r.amount, u.id) == -10) {
      printf("\n\t\t✗ The amount you choose to withdraw is superior to your "
             "available balance! \n\n");
      choose_exit_or_menu(u);
    }
    printf("\n\n\t\tSuccess");
  } else if (choice == 2) {
    printf("\n\t\tEnter the amount you want to deposit: ");
    if (!parseFloat(&r.amount)) {
      printf("\n\t\tInvalid Input\n\n");
      choose_exit_or_menu(u);
    }

    if (r.amount < 1) {
      printf("\n\t\tInvalid amount to deposit!\n\n");
      choose_exit_or_menu(u);
    }
    deposit_to_account(r.accountNbr, r.amount, u.id);
    printf("\n\t\tSuccess!\n\n");
  }
  choose_exit_or_menu(u);
}
