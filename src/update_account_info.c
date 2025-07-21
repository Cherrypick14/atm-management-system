#include "header.h"
#include "queries/queries.h"
#include "unistd.h"
#include <stdio.h>

void updateAccountInfo(struct User u) {
  struct Record record;
  int choice;
  char temp[100];
  char phone_temp[100];

  int userId = get_user_id(u.name);
prompt:
  system("clear");
  printf("\n\t\tEnter the account number you want to change:");
  scanf("%s", temp);

  /* Atoi function to check for valid entry of intergers only. -1 is returned if
   * the input contains characters*/
  if (atm_atoi(temp) == -1) {
    printf("\n\t\tInvalid input.\n");
    sleep(1);
    goto menu;
  }

  /* convert and assigning the value to records.accountNbr */
  record.accountNbr = atm_atoi(temp);
  temp[0] = '\n'; /*clear the temp variable*/

  /* checks if the user really owns the account whos records wants to be
  modified */
  if (!owns_account(record.accountNbr, userId)) {
    printf("\n\t\tInvalid account!");
    goto menu;
  }

  printf("\n\t\tWhich information you want to update?");
  printf("\n\t\t\t1->Phone Number");
  printf("\n\t\t\t2->Country\n");
  scanf("%d", &choice);

  if (choice == 1) {
    system("clear");
    printf("\n\t\tEnter the new phone number:");
    scanf("%s", phone_temp);

    /* Atoi function to check for valid entry of intergers only. -1 is returned
     * if the input contains characters*/
    if (atm_atoi(phone_temp) == -1) {
      printf("\n\t\tInvalid input.\n");
      sleep(1);
      goto menu;
    }
    record.phone = atm_atoi(phone_temp);

    if (update_phone(record.accountNbr, record.phone, userId) == SQLITE_OK) {
      printf("\n\t\t✓ Successfully changed phone!");
      sleep(1);
      goto menu;
    }
    printf("An error occured. \n");
  } else if (choice == 2) {
    system("clear");
    printf("\n\t\tEnter country:");
    read_string(record.country, sizeof(record.country));

    if (update_country(record.accountNbr, record.country, userId) ==
        SQLITE_OK) {
      printf("\n\t\tSuccessfully changed country!\n");
      sleep(1);
      goto menu;
    }
    printf("An error occured.");
  } else {
    printf("\n\t\tInvalid choice");
    goto menu;
  }
menu:
  mainMenu(u);
}
