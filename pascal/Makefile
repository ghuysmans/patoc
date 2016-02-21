#generate debug symbols
CFLAGS=-g
#generate headers
YFLAGS=-d
#track line number
LFLAGS=--yylineno

all: patoc
clean:
	rm pascal.c *.tab.h lexer.c *.o patoc

pascal.o: pascal.c
	mv y.tab.h pascal.tab.h 2>/dev/null
	$(CC) $(CFLAGS) -c -o $@ $<

patoc: patoc.o pascal.o lexer.c lexer.o
	$(CC) $(CFLAGS) -o $@ *.o -ll
