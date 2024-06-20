CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -g
LDFLAGS= -lMLV
EXEC=game.out
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

game.out: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

game.o: grid.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
