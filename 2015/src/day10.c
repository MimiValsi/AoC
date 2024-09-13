#include "misc.h"

void part1(char *puzzle);
void part2(char *puzzle);

int main() {
        char puzzle[1000] = "1113122113";
        // char puzzle[1000] = "1";
        part1(puzzle);
        // part2(puzzle);
}

void part1(char *puzzle) {
        u64 size = 100000000;
        char *res = malloc(size);
        strcpy(res, puzzle);
        u64 j = 0;
        u64 track = 0;
        for (u64 o = 0; o < 40; o++) {
                u64 len = strlen(puzzle);
                for (u64 i = 0; i < len; i++) {
                        j++;
                        if (res[i] != res[i + 1]) {
                                // printf("puzzle: %s\n", puzzle);
                                // printf("track = %d\n", track);
                                // printf("j = %d\n", j);
                                printf("> res = %s\n", res);
                                res[track++] = (j + '0');
                                // printf(">> res = %s\n", res);
                                // printf("j = %d\n", j);
                                // printf("track = %d\n", track);
                                res[track++] = res[i];
                                // printf(">>> res = %s\n", res);
                                j = 0;
                        }
                }
                if (strlen(res) > size) {
                        size *= 1000;
                        char *tmp = realloc(tmp, size);
                        if (!tmp) {
                                exit(-1);
                        }
                        res = tmp;
                }
                // printf("o = %d\n", o);
                // printf("> res: %s\n", res);
                strcpy(res, res);
                // printf(">> puzzle: %s\n", puzzle);
                track = 0;
                j = 0;
        }
        printf(">>> res = %s\n", res);
        printf("res len: %lu\n", strlen(res));
        free(res);
}

void part2(char *puzzle) {}
