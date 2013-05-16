CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -Iinclude
LFLAGS = -Wall $(DEBUG)

cc : main.o compiler.o
	$(CC) $(LFLAGS) -o bin/cc bin/main.o bin/compiler.o bin/lexer.o bin/utils.o

main.o : include/compiler.h
	$(CC) $(CFLAGS) -o bin/main.o core/main.c

compiler.o : include/compiler.h include/lexer.h include/utils.h include/core.h include/code.h
	$(CC) $(CFLAGS) -o bin/compiler.o core/compiler.c

lexer.o : include/lexer.h include/core.h include/utils.h
	$(CC) $(CFLAGS) -o bin/lexer.o core/lexer.c

utils.o : include/utils.h include/core.h
	$(CC) $(CFLAGS) -o bin/utils.o core/utils.c

clean:
	rm -f bin/*
