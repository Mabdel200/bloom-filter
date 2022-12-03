# My variables and Flags
CC = gcc

CFLAGS = -c -Wall
# This target will compile all the files
all: start

start: main.o bloom.o
		$(CC) main.o bloom.o -o start

main.o: main.c
		$(CC) $(CFLAGS) main.c

bloom.o: bloom.c
		$(CC) $(CFLAGS) bloom.c
# this target will run program
run:
	./start

clean:
	rm -rf *o start 