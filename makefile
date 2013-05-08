CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -Iinclude
LFLAGS = -Wall $(DEBUG)

cc : main.o compiler.o lexer.o
	$(CC) $(LFLAGS) -o bin/cc bin/main.o bin/compiler.o bin/lexer.o

main.o : include/compiler.h include/utils.h
	$(CC) $(CFLAGS) -o bin/main.o core/main.c

compiler.o : include/compiler.h include/lexer.h include/utils.h include/time.h include/core.h include/code.h
	$(CC) $(CFLAGS) -o bin/compiler.o core/compiler.c

lexer.o : include/core.h include/io.h
	$(CC) $(CFLAGS) -o bin/lexer.o core/lexer.c

clean:
	rm -rf bin/*
