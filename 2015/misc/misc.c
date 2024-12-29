#include "misc.h"

#define SIZE 60
/* Read the file, go to the end, return the length and go back to the beginning.
 * Return the length
 */
uint32_t get_file_length(FILE *file)
{
	fseek(file, 0, SEEK_END);
	uint32_t length = ftell(file);
	rewind(file);

	return length;
}

// Use strtok to split a string into words and add them to an array of strings.
// In this case, a struct with arr[[x]][[y]]
String line_split(char *line, char *delim)
{
	uint32_t i = 0;
	String str = { 0 };
	char *token = strtok(line, delim);
	while (token) {
		strcpy(str.s[i], token);
		token = strtok(NULL, delim);
		i++;
	}

	return str;
}

/* Read the file, and return line without '\n' */
char *get_line(FILE *file)
{
	char *line = malloc(SIZE + 1);
	if (!line) {
		perror("ERROR: Couldn't allocate memory.");
		exit(-1);
	}
	for (uint32_t i = 0;; i++) {
		line[i] = fgetc(file);
		if (line[i] == '\n') {
			line[i] = '\0';
			return line;
		}
	}

	return NULL;
}

// check array length.
uint32_t arr_length(int32_t *arr)
{
	int32_t n = 0;
	for (int32_t i = 0; arr[i] != '\0'; i++) {
		n++;
	}

	return n;
}

// Check for biggest number in a array
int32_t max_elem(int32_t *arr, uint32_t size)
{
	int32_t max = arr[0];
	for (uint32_t i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	return max;
}

// Check for the lowest number in a array
int32_t min_elem(int32_t *arr, uint32_t size)
{
	int32_t min = arr[0];
	for (uint32_t i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	return min;
}
