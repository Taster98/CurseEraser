#Chosen compiler
CC = gcc

#Flags
CFLAGS = -Wall

#Path
PERC = "PATH"

#clean phony to clean stuffs
.PHONY: uninstall clean test exe

all: ./curseEraser install

./curseEraser: ./curseEraser.c
	$(CC) $@.c $(CFLAGS) -o $@

install:
	@echo 'Installing curseEraser... \n';
	chmod +x setup.sh;
	./setup.sh;
	$(CC) $(CFLAGS) curseEraser.c -o curseEraser
	>> ~/.bashrc echo "export PATH=$$$(PERC):$(CURDIR)";
	@echo '\nCOMPLETED\nCurseEraser is installed. Write curseEraser -h or curseEraser --help to learn how to use it!';

clean: 
	echo Clean useless stuff
	rm -f ./curseEraser

uninstall:
	@echo 'Uninstalling curseEraser...\n'
	rm -f ./curseEraser ./curseEraser.c;
	rm -r ./error
	rm -r ./src
	sed '/curseEraser/d' -i ~/.bashrc;
	@echo '\nCOMPLETED\nUninstall complete. You can now delete this folder.';
