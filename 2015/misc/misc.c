#include "misc.h"

#define SIZE 60
/* Read the file, go to the end, return the length and go back to the beginning.
 * Return the length
 */
u64
get_file_length(FILE* file)
{
        fseek(file, 0, SEEK_END);
        u32 length = ftell(file);
        rewind(file);

        return length;
}

// Use strtok to split a string into words and add them to an array of strings.
// In this case, a struct with arr[[x]][[y]]
String
line_split(char *line, char *delim)
{
        u32 i = 0;
        String str = {0};
        char *token = strtok(line, delim);
        while(token) {
                strcpy(str.s[i], token);
                token = strtok(NULL, delim);
                i++;
        }

        return str;
}

/* Read the file, and return line without '\n' */
char*
get_line(FILE *file)
{
        char *line = malloc(SIZE * sizeof(char) + 1);
        if (!line) {
                perror("ERROR: Couldn't allocate memory.");
                exit(-1);
        }
        for(i32 i = 0;;i++) {
                line[i] = fgetc(file);
                if (line[i] == '\n') {
                        line[i] = '\0';
                        return line;
                }
        }

        return NULL;
}

// check array length.
u32
arr_length(i32 *arr) {
  i32 n = 0;
  for (i32 i = 0; arr[i] != '\0'; i++) {
    n++;
  }

  return n;
}

// Check for biggest number in a array
i32
max_elem(i32 *arr, u32 size)
{
        i32 max = arr[0];
        for (u32 i = 0; i < size; i++) {
                if (arr[i] > max) {
                        max = arr[i];
                }
        }

        return max;
}

// Check for the lowest number in a array
i32
min_elem(i32 *arr, u32 size)
{
        i32 min = arr[0];
        for (u32 i = 0; i < size; i++) {
                if (arr[i] < min) {
                        min = arr[i];
                }
        }

        return min;
}
