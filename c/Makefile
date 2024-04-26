CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

SRC := $(wildcard *.c)
EXEC := hangman

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXEC)
