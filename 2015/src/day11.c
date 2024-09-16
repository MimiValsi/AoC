#include "misc.h"
#include <stdio.h>

void part1(char *puzzle);
void part2(char *puzzle);

int main() {
        char *puzzle = "hepxcrrq";

        part1(puzzle);
        // part2(puzzle);
}

void part1(char *puzzle) {
        char res[10] = {0};
        strcpy(res, puzzle);

        // TODO: increment 3 letters minimun
        // Must skip 'i', 'o', 'l'
        // Must contain >= 2 non-overlapping pairs of letters

        printf("start: %s\n", res);
        u32 len = strlen(res);
        // printf("res: %c\n", res[0]);
        // int track = 0;
        for (int i = 1; i < len; i++) {
                for (int j = len - 1; res[j] <= 'z'; res[j]++) {
                        if (res[j] == 'z') {
                                res[j] = 'a';
                                res[j - i]++;
                                break;
                        }
                        printf("res: %s\n", res);
                }
                printf("> res: %s\n", res);
        }
}

void part2(char *puzzle) {}
