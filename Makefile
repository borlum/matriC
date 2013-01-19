# Compiler to use
CC=gcc
# Compiler flags
CFLAGS= -std=c99 -c -Wall

all: ma3c

ma3c: matrix.o ma3.o
	$(CC) -std=c99 matrix.o ma3.o -o ma3c

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c

ma3.o: ma3.c
	$(CC) $(CFLAGS) ma3.c

clean:
	rm -f *.o ma3c