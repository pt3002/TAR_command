CC = gcc
CFLAGS = -Wall -Werror -O2

tar: main.o options.o createoptionfns.o bitfilecreation.o lz77.o tree.o bitio.o extract.o
		$(CC) $(CFLAGS) -o tar main.o options.o createoptionfns.o bitfilecreation.o lz77.o tree.o bitio.o extract.o -lm
	
main.o: main.c 
		$(CC) $(CFLAGS) -c main.c

options.o: options.c options.h
		$(CC) $(CFLAGS) -c options.c

createoptionfns.o: createoptionfns.c createoptionfns.h
		$(CC) $(CFLAGS) -c createoptionfns.c

bitfilecreation.o: bitfilecreation.c bitfilecreation.h bitio.h lz77.h
		$(CC) $(CFLAGS) -c bitfilecreation.c

lz77.o: lz77.c bitio.h tree.h
		$(CC) $(CFLAGS) -c lz77.c

tree.o: tree.c tree.h
		$(CC) $(CFLAGS) -c tree.c

bitio.o: bitio.c bitio.h 
		$(CC) $(CFLAGS) -c bitio.c 
	
extract.o: extract.c extract.h
		$(CC) $(CFLAGS) -c extract.c