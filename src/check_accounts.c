#include "header.h"
#include "queries/queries.h"
#include <stdio.h>

void choose_exit_or_menu(struct User u) {
  char choice[10];
invalid:
  printf("\n\t\tEnter 1 to go to main menu and 0 to exit.\n");
  scanf("%s", choice);
  if (atm_atoi(choice) == 1) {
    mainMenu(u);
  } else if (atm_atoi(choice) == 0) {
    exit(0);
  } else {
    printf("Insert a valid operation");
    goto invalid;
  }
}
void checkAllAccounts(struct User u) {
  int choice;
  system("clear");
  int user_id = get_user_id(u.name);

  printf("\n\t\t========= All Accounts  =========\n\n");
  if (check_user_accounts(user_id) != SQLITE_OK) {
    printf("\n\t\tAn error occured.\n");
  }
  choose_exit_or_menu(u);
};
