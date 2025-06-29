#include "misc.h"

#define SIZE 100

/* Read the file, go to the end, return the length and go back to the beginning.
 * Return the length
 */
long get_file_length(FILE *file)
{
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	rewind(file);

	return length;
}

// Use strtok to split a string into words and add them to an array of strings.
// In this case, a struct with arr[[x]][[y]]
char **line_split(char *line, char *delim)
{
	uint32_t i = 0;
	uint32_t size = 20;

	char **strs = malloc(size * sizeof(char *));

	char *token = strtok(line, delim);

	while (token) {
		if (i >= size) {
			size *= 2;
			char **tmp = realloc(strs, size);
			if (!tmp) {
				free_strs(strs);
				return NULL;
			}
			strs = tmp;
		}
		strs[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}

	return strs;
}

// use only to free array of strings used with line_split() func
// which will end with NULL
void free_strs(char **strs)
{
	for (int i = 0;; i++) {
		if (strs[i] == NULL) {
			break;
		}
		free(strs[i]);
	}

	free(strs);
}

/* Read the file, and return line without '\n' */
char *get_line(FILE *file)
{
	char *line = malloc(SIZE + 1);
	if (!line) {
		perror("ERROR: Couldn't allocate memory.");
		exit(EX_MALLOC);
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

uint32_t nb_lines_file(char *filename, char delim)
{
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("file doesn't exist");
		exit(EXIT_FAILURE);
	}

	uint32_t ret = 0;
	char c;
	for (c = fgetc(file); c != EOF; c = fgetc(file)) {
		if (c == delim)
			ret++;
	}

	fclose(file);

	return ret;
}
