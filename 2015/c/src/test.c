#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int size = 2;
	char **str = malloc(size * sizeof(char *));
	if (!str) {
		printf("error alloc\n");
		exit(EX_FAIL);
	}

	int i;
	for (i = 0; i < 10; i++) {
		if (i >= size) {
			size *= 2;
			char **tmp = realloc(str, size * sizeof(char *));
			if (tmp == NULL) {
				return EX_REALLOC;
			}
			str = tmp;
		}
		str[i] = strdup("hello");
		printf("str: %s\n", str[i]);
	}

	for (int i = 0; i < 10; i++) {
		free(str[i]);
	}
	free(str);

	return 0;
}
