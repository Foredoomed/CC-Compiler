CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -Isrc/include
LFLAGS = -Wall $(DEBUG)
MKDIR_P = mkdir -p

.PHONY: directories

all: directories hash utils lexer compiler main ccc

directories: bin

bin :
	${MKDIR_P} bin

ccc : main compiler
	$(CC) $(LFLAGS) -o bin/ccc bin/main.o bin/compiler.o bin/lexer.o bin/utils.o bin/hash.o

main : src/include/compiler.h
	$(CC) $(CFLAGS) -o bin/main.o src/core/main.c

compiler : src/include/compiler.h src/include/lexer.h src/include/utils.h src/include/core.h src/include/code.h src/include/hash.h
	$(CC) $(CFLAGS) -o bin/compiler.o src/core/compiler.c

lexer : src/include/lexer.h src/include/core.h src/include/utils.h
	$(CC) $(CFLAGS) -o bin/lexer.o src/core/lexer.c

utils : src/include/utils.h src/include/core.h
	$(CC) $(CFLAGS) -o bin/utils.o src/core/utils.c

hash : src/include/hash.h
	$(CC) $(CFLAGS) -o bin/hash.o src/core/hash.c

clean:
	rm -f bin/*
	rm -rf bin



