#!/bin/bash

FILE="libsqlite3.a"

if [ -f "$FILE" ]; then
	make && make clean
else
	curl -S https://www.sqlite.org/2024/sqlite-amalgamation-3460000.zip >sqlite-amalgamation-3460000.zip

	unzip sqlite-amalgamation-3460000.zip

	rm -r sqlite-amalgamation-3460000.zip

	cd sqlite-amalgamation-3460000/

	gcc -c sqlite3.c

	ar rcs libsqlite3.a sqlite3.o

	mv libsqlite3.a ../

	cd ../
	rm sqlite3.o

	rm -rf sqlite-amalgamation-3460000

	make && make clean
fi
