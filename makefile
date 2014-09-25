#compiler
CC=	gcc
#compilerflags
CFLAGS=		-Wall -ggdb -std=c99

all: db

db: db.o
	$(CC) $(CFLAGS) -o db db.o

db.o: db.c
	$(CC) $(CFLAGS) -c db.c

run: all
	./db databases/SWE.db

.PHONY: clean

clean:
	rm *~
