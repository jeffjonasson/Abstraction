#compiler
CC=	gcc
#compilerflags
CFLAGS=		-Wall -ggdb -std=c99

all: db

db: db.o functions.o
	$(CC) $(CFLAGS) -o db db.o functions.o

db.o: db.c
	$(CC) $(CFLAGS) -c db.c

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c

run: all
	./db databases/SWE.db

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf *#

test: unittests.c functions.c header.h
	$(CC) $(CFLAGS) -o -lcunit unittests unittests.c functions.c

testrun: unittests.c functions.c header.h
	$(CC) $(CFLAGS) -o -lcunit unittests unittests.c functions.c
	./unittests
