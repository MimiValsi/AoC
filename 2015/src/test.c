#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Foo foo_t;

typedef struct Foo {
	u32 index;
	char *str;
	foo_t *next;
	foo_t *prev;
} foo_t;

void check_curly_brackets(const char *str, u32 len, foo_t **head);

foo_t *ll_new(u32 index, const char *str);
void ll_insert_at_beginning(foo_t **head, u32 index, const char *str);

int main()
{
	FILE *file = fopen("./data/day12_2.txt", "r");
	u32 len = get_file_length(file);
	// copy to array coz it's easier to control the loop flow
	char str[len];
	fgets(str, len, file);
	printf("\nfull string: %s\n\n", str);

	// foo_append() will make the rest
	foo_t *obj = NULL;
	// obj = ll_new(1, );
	// ll_insert_at_beginning(&obj, 1, "red");
	// ll_insert_at_beginning(&obj, 2, "blue");
	// check_curly_brackets(str, len, &obj);

	fclose(file);

	return 0;
}

// this may/will be recursive!
void check_curly_brackets(const char *str, u32 len, foo_t **head)
{
	// copy str to this temporary variable so I can control the obj index!
	char tmp[1000];
	memset(tmp, 0, 1000);
	u32 t = 0;

	// static var
	static u32 position = 1;
	for (u32 i = 0; i < len; i++) {
		// copy string
		tmp[t] = str[i];
		t++;

		if (str[i] == '}') {
			position--;
			printf("position--: %s\n", tmp);
			break;
		}
		if (i != 0 && str[i + 1] == '{') {
			position++;
			printf("position++: %s\n", tmp);
			break;
		}
	}
}

foo_t *ll_new(u32 index, const char *str)
{
	if (!str) {
		perror("str must not be NULL!");
		return NULL;
	}

	foo_t *new = malloc(sizeof(*new));
	if (!new) {
		perror("couldn't allocate new ll");
		return NULL;
	}

	new->index = index;
	new->str = strdup(str);
	new->next = NULL;
	new->prev = NULL;

	return new;
}

void ll_insert_at_beginning(foo_t **head, u32 index, const char *str)
{
	foo_t *new = ll_new(index, str);
	if (!(*head)) {
		*head = new;
		return;
	}

	new->next = *head;
	(*head)->prev = new;
	*head = new;
}

void ll_append(foo_t **head, u32 index, const char *str)
{
	foo_t *new = ll_new(index, str);
	if (!(*head)) {
		*head = new;
		return;
	}

	foo_t *tmp = *head;
	while (tmp->next) {
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
}
