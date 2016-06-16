//Simplified LL(1) Pascal type expression checker


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//taken from http://stackoverflow.com/a/10966395
#define ENUM(X) X,
#define STR(X) #X,
#define FOREACH_TOKEN(TOKEN) \
	TOKEN(END) \
	TOKEN(HAT) \
	TOKEN(ID) \
	TOKEN(ARRAY) \
	TOKEN(L) \
	TOKEN(R) \
	TOKEN(OF) \
	TOKEN(INTEGER) \
	TOKEN(CHAR) \
	TOKEN(NBR) \
	TOKEN(DOTDOT)
enum token {FOREACH_TOKEN(ENUM)};
static const char *token_str[] = {FOREACH_TOKEN(STR) NULL};

enum token *token;
const char *expected = NULL; //part of the error message

int match(enum token x) {
	if (*token == x) {
		token++;
		return 1;
	}
	else {
		expected = token_str[x];
		return 0;
	}
}


int simple() {
	if (*token == NBR)
		return match(NBR) && match(DOTDOT) && match(NBR);
	else if (*token==INTEGER || *token==CHAR)
		return match(*token);
	else {
		expected = "a simple type";
		return 0;
	}
}

int type() {
	if (*token==NBR || *token==INTEGER || *token==CHAR)
		return simple(); //useless call
	else if (*token == HAT)
		return match(HAT) && match(ID);
	else if (*token == ARRAY) {
		return match(ARRAY) && match(L) && simple() && match(R) &&
			match(OF) && type(); //right-recursion
	}
	else {
		expected = "a complex type";
		return 0;
	}
}


int main(int argc, char *argv[]) {
	if (token = calloc(argc, sizeof(enum token))) {
		enum token *p = token;
		int ret = 0;
		argv++;
		while (--argc) {
			const char ** s = token_str;
			enum token t = 0;
			while (*s) {
				if (!strcmp(*argv, *s)) {
					*p = t;
					break;
				}
				t++;
				s++;
			}
			if (!*s) {
				fprintf(stderr, "unknown token %s\n", *argv);
				free(token);
				return 1;
			}
			p++;
			argv++;
		}
		*p = END;
		p = token; //we want to free it afterwards
		if (!type() || !match(END)) {
			const char *current = token_str[*token];
			fprintf(stderr, "expected %s, got %s\n", expected, current);
			ret = 2;
		}
		free(p);
		return ret;
	}
	else {
		fprintf(stderr, "insufficient memory\n");
		return -1;
	}
}
