CC = gcc
CFLAGS = -Wall -Werror -O2

tar: main.o options.o createoptionfns.o lz77.o tree.o bitio.o
		$(CC) $(CFLAGS) -o tar main.o options.o createoptionfns.o lz77.o tree.o bitio.o -lm
	
main.o: main.c bitio.h lz77.h 
		$(CC) $(CFLAGS) -c main.c

options.o: options.c options.h
		$(CC) $(CFLAGS) -c options.c

createoptionfns.o: createoptionfns.c createoptionfns.h
		$(CC) $(CFLAGS) -c createoptionfns.c

lz77.o: lz77.c bitio.h tree.h
		$(CC) $(CFLAGS) -c lz77.c

tree.o: tree.c tree.h
		$(CC) $(CFLAGS) -c tree.c

bitio.o: bitio.c bitio.h 
		$(CC) $(CFLAGS) -c bitio.c 