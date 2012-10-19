CC=gcc
CFLAGS=-ansi -pedantic -Wall -O -g

sort: indexer.c sorted-list.o tokenizer.o
	$(CC) $(CFLAGS) indexer.c sorted-list.o tokenizer.o -o indexer

sorted-list.o: sorted-list.c sorted-list.h
	$(CC) $(CFLAGS) -c sorted-list.c

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CFLAGS) -c tokenizer.c

clean:
	rm -rf *.o indexer
