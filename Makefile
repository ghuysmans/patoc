#generate debug symbols
CFLAGS=-g
#generate headers
YFLAGS=-d
#track line number
LFLAGS=--yylineno

all: patoc types
clean:
	rm pascal.c *.tab.h lexer.c *.o patoc

pascal.o: pascal.c
	mv y.tab.h pascal.tab.h 2>/dev/null
	$(CC) $(CFLAGS) -c -o $@ $<

patoc: pascal.o patoc.o lexer.c lexer.o
	$(CC) $(CFLAGS) -o $@ *.o -ll
