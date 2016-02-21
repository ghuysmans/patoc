#include <stdio.h>
#include "pascal.tab.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: %s source.pas\n", argv[0]);
		return 1;
	}
	yyparse();
	return 0;
}
