#pragma 1
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NL() printf("\n")
#define ARRAY_LEN(x) (sizeof x / sizeof x[0])

long get_file_length(FILE *file);
char **line_split(char *line, char *delim);
char *get_line(FILE *file);
int32_t *str_to_int_array(char *line, uint32_t len);
uint32_t arr_length(int32_t *arr);
int32_t max_elem(int32_t *arr, uint32_t size);
int32_t min_elem(int32_t *arr, uint32_t size);
void *alloc_2D_array(uint32_t rows, uint32_t cols);
void free_2D_array(int64_t **arr, uint32_t rows);
uint32_t nb_lines_file(char *filename, char delim);
void free_strs(char **strs);

enum misc_exit { EX_SUCCESS, EX_FAIL, EX_MALLOC, EX_REALLOC };
