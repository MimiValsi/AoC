#pragma 1
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Haven't figure it out how to create a pointer of pointers
// like char str[x][y]
typedef struct {
	char s[10][20];
} String;

#define NL() printf("\n")
#define ARRAY_LEN(x) (sizeof x / sizeof x[0])

uint32_t get_file_length(FILE *file);
String line_split(char *line, char *delim);
char *get_line(FILE *file);
int32_t *str_to_int_array(char *line, uint32_t len);
uint32_t arr_length(int32_t *arr);
int32_t max_elem(int32_t *arr, uint32_t size);
int32_t min_elem(int32_t *arr, uint32_t size);
void *alloc_2D_array(uint32_t rows, uint32_t cols);
void free_2D_array(int64_t **arr, uint32_t rows);
