#include "sqlite3.h"
#include "stdbool.h"

extern sqlite3 *db;

int initialize_db_conn();
void close_db_con();
int get_user_id(char *username);
void log_error(const char *error);
char *get_user_pass(char name[50]);
int insert_user(char name[50], char password[50]);
void initialize_all_databases();
int update_country(int acc_number, char *country, int user_id);
int update_phone(int acc_number, int phone, int user_id);
bool owns_account(int acc_number, int user_id);
int check_user_accounts(int user_id);
int check_account_record(int acc_number, int user_id);
bool check_acc_number(int accountNbr);
double check_amount(int account_number);
int deposit_to_account(int account_number, double amount_to_deposit,
                       int user_id);
int withdraw_from_account(int account_number, double amount_to_deduct,
                          int user_id);
int delete_account(int accountNbr, int user_id);
int transfer_account(int userID, int accountNumber);
int account_type(int accountNumber);
