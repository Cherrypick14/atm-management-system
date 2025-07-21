# ATM MANAGEMENT SYSTEM

This repository contains a simple **ATM (Automated Teller Machine)** program implemented in `C` and `sqlite3 database` for storing user credentials and records. 

The program simulates basic banking operations, including:

1. *Creating new account*

2. *Updating account information*

3. *Checking accounts*

4. *Checking list of owned accounts*

5. *Make transaction*

6. *Remove an existing account*

7. *Transfer ownership*

#### *Prerequisites*

Make sure you have `gcc` and `bash` installed on your system before continuing.

#### *Cloning and setup*

To clone the project.

```bash
git https://github.com/Cherrypick14/atm-management-system.git
cd atm-management-system
```

Run the compiler shell script to download necessarry files and compile the project.

```bash
sh compiler.sh
```

The compiler shell script first checks if compiled `libsqlite3.a`, static library that contains the compiled object file(s).

The static library is then linked with the  application during the final build process.

To execute the built binary file of the project , run 

```bash
./atm
```

You may either choose to create your own account to explore the ATM program or login with one of the below credentials.

```textile
Username: Alice 
Password: q1w2e3r4t5y6


Username: Michel 
Password: q1w2e3r4t5y6
```

*Password hashing algorithm* : The project uses `ROT13` algorithm for hashing user passwords before storing them in the sqlite database.



***Creating an account.***

Creating account has a feature which you cannot add a month greater than `12` and year `must` be between the year `1900` - `2100`. if not the account won't be created.

***Password Encryption***

This project utilizes ROT13 algorithm for password Encryption which isnt that very secure for production.


