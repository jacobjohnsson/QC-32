CC=gcc
CFLAGS=-g
SRC=src/main.c src/main.h src/debug.h src/debug.c

hello: 
	$(CC) $(CFLAGS) -o QC-32 $(SRC) && ./QC-32
