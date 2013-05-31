CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -Iinclude
LFLAGS = -Wall $(DEBUG)
MKDIR_P = mkdir -p

.PHONY: directories

all: directories hashmap utils lexer compiler main ccc

directories: bin

bin :
	${MKDIR_P} bin

ccc : main compiler
	$(CC) $(LFLAGS) -o bin/ccc bin/main.o bin/compiler.o bin/lexer.o bin/utils.o bin/hashmap.o

main : include/compiler.h
	$(CC) $(CFLAGS) -o bin/main.o core/main.c

compiler : include/compiler.h include/lexer.h include/utils.h include/core.h include/code.h
	$(CC) $(CFLAGS) -o bin/compiler.o core/compiler.c

lexer : include/lexer.h include/core.h include/utils.h
	$(CC) $(CFLAGS) -o bin/lexer.o core/lexer.c

utils : include/utils.h include/core.h
	$(CC) $(CFLAGS) -o bin/utils.o core/utils.c

hashmap : include/hashmap.h
	$(CC) $(CFLAGS) -o bin/hashmap.o core/hashmap.c

clean:
	rm -f bin/*
	rm -rf bin



