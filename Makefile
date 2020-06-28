#Chosen compiler
CC = gcc

#Flags
CFLAGS = -Wall

#clean phony to clean stuffs
.PHONY: clean

main: ./blasphemyEliminator

./blasphemyEliminator: ./blasphemyEliminator.c
	$(CC) $@.c $(CFLAGS) -o $@

clean: 
	echo Clean useless stuff
	rm -f ./blasphemyEliminator
