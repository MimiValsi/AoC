#include "misc.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1(FILE *file);
int part2(FILE *file);

char *get_all_file(FILE *file, u32 len);
int sum_numbers(const char *str, u32 i);
int pos_nb_sum(const char *all, u32 *i);
int neg_nb_sum(const char *all, u32 *i);
void zero_arr(char *arr);

int main(void)
{
	FILE *file = fopen("./data/day12.txt", "r");
	int p1 = part1(file);
	printf("part1: %d\n", p1);
	rewind(file);
	int p2 = part2(file);
	printf("part2: %d\n", p2);

	fclose(file);

	return 0;
}

int part1(FILE *file)
{
	u32 len = get_file_length(file);

	char all[len];
	for (int i = 0; i < len; i++) {
		all[i] = fgetc(file);
	}

	char tmp;
	int total = 0;
	for (u32 i = 0; i < len; i++) {
		if (isdigit(all[i])) {
			total += pos_nb_sum(all, &i);
		}
		if (all[i] == '-') {
			total += neg_nb_sum(all, &i);
		}
	}
	return total;
}

typedef struct Json json_t;

typedef struct Json {
	int32_t index;
	int32_t position;
	char *str;
	json_t *next;
	json_t *prev;
	bool red;
} json_t;

void check_curly_brackets(const char *str, uint32_t len, json_t **json);

json_t *init_json(const char *str, int32_t position, bool red, int32_t index);
void append_json(json_t **head, uint32_t position, const char *str, bool red,
		 int32_t index);
void free_json(json_t **head);
void print_json(json_t **head);
int pos_nb_sum(const char *all, uint32_t *i);
int neg_nb_sum(const char *all, uint32_t *i);
int32_t calculate(json_t **head);
int32_t calc(json_t *tmp);
bool check_red_position(json_t **head, uint32_t position);
void red_next(json_t *child);
void red_prev(json_t *child);

void check_red(json_t **head);

int part2(FILE *file)
{
	// FILE *file = fopen("./data/day12.txt", "r");
	uint32_t len = get_file_length(file);
	// copy to array coz it's easier to control the loop flow
	char str[len];
	fgets(str, len, file);

	json_t *json = NULL;
	check_curly_brackets(str, len, &json);
	check_red(&json);
	int32_t total = calculate(&json);

	// print_json(&json);
	free_json(&json);

	return total;
}

void check_curly_brackets(const char *str, uint32_t len, json_t **json)
{
	int size = 10000;
	char tmp[size];
	memset(tmp, 0, size);

	int32_t t = 1, pos = 0, index = 0;
	bool red = false;
	tmp[0] = '{';

	for (uint32_t i = 1; i < len - 1; i++) {
		tmp[t] = str[i];
		t++;
		if (str[i + 1] == '{') {
			tmp[t] = '\0';
			index++;
			red = strstr(tmp, ":\"red\"") ? true : false;
			append_json(json, pos, tmp, red, index);
			pos++;
			memset(tmp, 0, size);
			t = 0;
		}

		if (str[i] == '}') {
			tmp[t] = '\0';
			index++;
			red = strstr(tmp, ":\"red\"") ? true : false;
			append_json(json, pos, tmp, red, index);
			pos--;
			memset(tmp, 0, size);
			t = 0;
		}
	}
}

void check_red(json_t **head)
{
	for (int i = 0; i < 5; i++) {
		json_t *tmp = *head;
		while (tmp) {
			if (tmp->red) {
				json_t *child = tmp;
				red_next(child);
				red_prev(child);
			}

			tmp = tmp->next;
		}
	}
}

void red_next(json_t *child)
{
	int32_t index = child->index;
	int32_t position = child->position;
	child = child->next;
	while (child->next) {
		if (child->position == position && child->index != index) {
			child->red = true;
			return;
		}
		if (position < child->position) {
			child->red = true;
		} else {
			return;
		}
		child = child->next;
	}
	return;
}

void red_prev(json_t *child)
{
	int32_t index = child->index;
	int32_t position = child->position;
	child = child->prev;
	while (child->prev) {
		if (child->position == position && child->index != index) {
			child->red = true;
			return;
		}
		if (position < child->position) {
			child->red = true;
		} else {
			return;
		}
		child = child->prev;
	}

	return;
}

int32_t calculate(json_t **head)
{
	json_t *tmp = *head;
	int32_t total = 0;
	while (tmp) {
		if (!tmp->red) {
			total += calc(tmp);
		}
		tmp = tmp->next;
	}

	return total;
}

int32_t calc(json_t *tmp)
{
	int32_t sum = 0;
	for (uint32_t i = 0; i < strlen(tmp->str); i++) {
		if (isdigit(tmp->str[i])) {
			sum += pos_nb_sum(tmp->str, &i);
		}
		if (tmp->str[i] == '-') {
			sum += neg_nb_sum(tmp->str, &i);
		}
	}

	return sum;
}

int pos_nb_sum(const char *all, uint32_t *i)
{
	int total = 0;
	uint32_t o = 0;
	char nb[5] = { 0 };
	for (uint32_t j = *i; j < *i + 3; j++) {
		if (isdigit(all[j])) {
			nb[o] = all[j];
			o++;
		} else
			break;
	}
	*i += o;

	total += atoi(nb);

	return total;
}

int neg_nb_sum(const char *all, uint32_t *i)
{
	int total = 0;
	uint32_t o = 0;
	char nb[5] = { 0 };
	nb[o] = '-';
	o++;
	for (uint32_t j = *i + 1; j < *i + 3; j++) {
		if (isdigit(all[j])) {
			nb[o] = all[j];
			o++;
		} else
			break;
	}
	*i += o;
	total += atoi(nb);

	return total;
}
json_t *init_json(const char *str, int32_t position, bool red, int32_t index)
{
	if (!str) {
		perror("str must not be NULL!");
		return NULL;
	}

	json_t *new = malloc(sizeof(*new));
	if (!new) {
		perror("couldn't allocate new ll");
		return NULL;
	}

	new->position = position;
	new->index = index;
	new->str = strndup(str, strlen(str));
	new->red = red;
	new->next = NULL;
	new->prev = NULL;

	return new;
}

void append_json(json_t **head, uint32_t position, const char *str, bool red,
		 int32_t index)
{
	// create new object at the end
	json_t *new = init_json(str, position, red, index);
	if (!(*head)) {
		*head = new;
		return;
	}

	json_t *tmp = *head;
	while (tmp->next) {
		tmp = tmp->next;
	}

	tmp->next = new;
	new->prev = tmp;
}

void free_json(json_t **head)
{
	if (*head == NULL) {
		return;
	}
	json_t *tmp = NULL;
	while (*head) {
		tmp = *head;
		*head = (*head)->next;
		free(tmp->str);
		free(tmp);
	}
}

void print_json(json_t **head)
{
	json_t *tmp = *head;
	printf("object:\n");
	while (tmp) {
		printf("index: %d\nposition: %d\nstring: %s\n", tmp->index,
		       tmp->position, tmp->str);
		printf("red: %s\n\n", (tmp->red == 1 ? "true" : "false"));
		tmp = tmp->next;
	}
}
