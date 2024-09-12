#include "misc.h"
#include <stdio.h>

void part1(char *puzzle);
void part2(char *puzzle);

int main() {
        // char puzzle[1000] = "1113122113";
        char puzzle[1000] = "1";
        part1(puzzle);
        // part2(puzzle);
}

void part1(char *puzzle) {
        char res[20] = {0};
        u32 j = 0;
        u32 track = 0;
        for (u32 o = 0; o < 40; o++) {
                u32 len = strlen(puzzle);
                for (u32 i = 0; i < len; i++) {
                        j++;
                        if (puzzle[i] != puzzle[i + 1]) {
                                printf("puzzle: %s\n", puzzle);
                                // printf("track = %d\n", track);
                                // printf("j = %d\n", j);
                                // printf("> res = %s\n", res);
                                res[track++] = (j + '0');
                                // printf(">> res = %s\n", res);
                                // printf("j = %d\n", j);
                                // printf("track = %d\n", track);
                                res[track++] = puzzle[i];
                                // printf(">>> res = %s\n", res);
                                j = 0;
                        }
                }
                // printf("o = %d\n", o);
                // printf("> puzzle: %s\n", puzzle);
                strcpy(puzzle, res);
                // printf(">> puzzle: %s\n", puzzle);
                track = 0;
                j = 0;
        }
        printf(">>> res = %s\n", res);
}

void part2(char *puzzle) {}
