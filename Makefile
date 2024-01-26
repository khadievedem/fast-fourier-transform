CC=gcc
STD=c89
CFLAGS=-std=$(STD)
SRC=main.c
OUT=main.o


all: main.c
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

PHONY: clean

clean:
	rm -f ./*.o
