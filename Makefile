CC=gcc

SRCS=$(wildcard ./src/*.c ./src/queries/*.c)
OBJS=$(SRCS:.c=.o)


MAIN=atm

all:    $(MAIN)
	@echo  Program has been compiled.

$(MAIN): $(OBJS) 
	$(CC) -o $(MAIN) $(OBJS) libsqlite3.a

clean :
	rm -f $(OBJS) ./src/queries/*.o
