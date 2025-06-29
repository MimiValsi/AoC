#include "misc.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1(FILE *file, char *filename);
int part2(FILE *file, char *filename);

bool check_table_if_person_exists(char *name, char **persons);
void free_array(char **persons, int len);

int main(void)
{
	char *filename = "./data/test.txt";
	// char *filename = "./data/day13.txt";
	// FILE *file = fopen("./data/day13.txt", "r");
	FILE *file = fopen(filename, "r");

	int p1 = part1(file, filename);
	printf("p1: %d\n", p1);
	// rewind(file);
	// int p2 = part2(file);
	// printf("p2: %d\n", p2);
	fclose(file);
	return EX_SUCCESS;
}

int part1(FILE *file, char *filename)
{
	uint32_t lines_nb = nb_lines_file(filename, '\n');

	/*
	 * [0]
	 * = first person
	 * [2]  = gain
	 * [3]  = 54
	 * [10] = second person
	 */

	// track first person
	uint32_t t = 0;

	/*
	 * starting point
	 * allocate the number of lines of the file 
	 */
	char **lines = malloc(lines_nb * sizeof(char *));
	for (int i = 0; i < lines_nb; i++) {
		lines[i] = get_line(file);
	}

	// 10 bytes alloc
	size_t bytes = 10;
	char fp[bytes];
	char sp[bytes];
	memset(fp, '\0', bytes);
	memset(sp, '\0', bytes);

	// total sum added/substracted
	int total = 0;

	// add/subtract depending who's next
	int nb = 0;

	// bad string
	// String str = { 0 };
	char **persons = NULL;

	// table array returns all ppl sitted
	char table[10][10] = { 0 };
	// char **persons[10][10] = { 0 };

	// track line
	// there's 7 people, jump 7 lines to fetch an unique line
	// uint32_t jump = 7; // puzzle file

	uint32_t jump = 3; // test file
	// persons = line_split(lines[0], " ");

	// loop over as many line_nb, add/subtract the first person, add it to the list.
	for (uint32_t i = 0; i < lines_nb; i++) {
		// for (uint32_t i = 0; i < 1; i++) {
		persons = line_split(lines[i], " ");
		printf("persons[0]: %s\n", persons[0]); // first person
		printf("persons[2]: %s\n", persons[2]); // gain / lose
		printf("persons[3]: %s\n", persons[3]); // 23 / -3
		printf("persons[10]: %s\n", persons[10]); // second person

		if (strcmp(persons[2], "gain") == 0) {
			total += atoi(persons[3]);
		}
		if (strcmp(persons[2], "lose") == 0) {
			total -= atoi(persons[3]);
		}
		// for (uint32_t j = i + jump; j < lines_nb; j++) {
		// 	printf("persons: %s\n", lines[j]);
		// }

		bool exists = check_table_if_person_exists(persons[0], persons);
		free_array(persons, 11);
		break;
	}

	// free lines
	free_array(lines, lines_nb);
	return total;
}

void free_array(char **persons, int len)
{
	for (int i = 0; i < len; i++)
		free(persons[i]);

	free(persons);
}

// Check if the person is already exist in the persons
// 1st check first person then check the second one.
// if the 1st person returns true, then we can skip as many as it exists till next one.
// then check for the second one, it must return 1 time false and as much as it exists true.
bool check_table_if_person_exists(char *name, char **persons)
{
	for (int i = 0; i < 11; i++) {
		if (strcmp(name, persons[i]) == 0) {
			printf("found %s\n", name);
			return true;
		}
	}
	return false;
}

int part2(FILE *file, char *filename)
{
	int total = 0;

	return total;
}
