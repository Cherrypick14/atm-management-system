#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Date {
  int month, day, year;
};

// all fields for each record of an account
struct Record {
  int id;
  int userId;
  char name[100];
  char country[100];
  int phone;
  char accountType[10];
  int accountNbr;
  double amount;
  struct Date deposit;
  struct Date withdraw;
};

struct User {
  int id;
  char name[50];
  char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void checkAccount(struct User u);
void makeTransaction(struct User u);
void transferAccount(struct User u);

// Other functions
int atm_atoi(const char *input);
void updateAccountInfo(struct User u);
int new_record(struct Record r, char *name);
void read_string(char *buffer, size_t size);
void choose_exit_or_menu(struct User u);
void deleteAccount(struct User u);
int account_info(int accountNumber, int user_id);
void rot13(char *str);
bool parseFloat(double *myDouble);