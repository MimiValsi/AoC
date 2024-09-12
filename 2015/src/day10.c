#include "misc.h"
#include <stdio.h>

void part1(char *puzzle);
void part2(char *puzzle);

int main() {
        // char *puzzle = "1113122113";
        char *puzzle = "1";
        part1(puzzle);
        // part2(puzzle);
}

void part1(char *puzzle) {
        u32 len = strlen(puzzle);
        char res[20] = {0};
        u32 j = 0;
        u32 track = 0;
        for (u32 i = 0; i < len - 1; i++) {
                if (puzzle[i] != puzzle[i + 1]) {
                        res[track++] = j;
                        res[track++] = puzzle[i - 1];
                        j = 1;
                }
                j++;
                // break;
        }
        printf("res = %s\n", res);
}

void part2(char *puzzle) {}
