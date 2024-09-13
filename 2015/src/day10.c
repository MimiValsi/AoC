#include "misc.h"
#include <stdio.h>

u64 part1(char *puzzle);
u64 part2(char *puzzle);

int main() {
        char puzzle[1000] = "1113122113";

        printf("part1: %lu\n", part1(puzzle));
        part2(puzzle);
        printf("part2: %lu\n", part2(puzzle));
}

u64 part1(char *puzzle) {
        // random size which is high enough to not realloc
        u64 size = 400000000;
        char *res = calloc(size, sizeof(*res));
        if (!res) {
                printf("res malloc\n");
                exit(-1);
        }
        // copy 1 time puzzle in res
        // this var will be reused
        strcpy(res, puzzle);

        // j counts how many time the same number appear, it's reset each time
        // the next number isn't the same.
        // track it means to avoid copying in the same place.
        // len, just the length of the "new" string
        u64 j = 0, track = 0, len = 0;

        for (u64 o = 0; o < 40; o++) {
                // tmp var which will be created and then copy to res var
                char *tmp_s = calloc(size, sizeof(*tmp_s));
                if (!tmp_s) {
                        printf("malloc tmp_s\n");
                        exit(-1);
                }

                len = strlen(res);
                for (u64 i = 0; i < len; i++) {
                        j++;
                        if (res[i] != res[i + 1]) {
                                tmp_s[track++] = (j + '0');
                                tmp_s[track++] = res[i];
                                j = 0;
                        }
                }
                strcpy(res, tmp_s);
                track = 0;
                j = 0;
                free(tmp_s);
        }
        len = strlen(res);

        free(res);

        return len;
}

u64 part2(char *puzzle) {
        // random size which is high enough to not realloc
        u64 size = 400000000;
        char *res = calloc(size, sizeof(*res));
        if (!res) {
                printf("res malloc\n");
                exit(-1);
        }
        // copy 1 time puzzle in res
        // this var will be reused
        strcpy(res, puzzle);

        // j counts how many time the same number appear, it's reset each time
        // the next number isn't the same.
        // track it means to avoid copying in the same place.
        // len, just the length of the "new" string
        u64 j = 0, track = 0, len = 0;

        for (u64 o = 0; o < 50; o++) {
                // tmp var which will be created and then copy to res var
                char *tmp_s = calloc(size, sizeof(*tmp_s));
                if (!tmp_s) {
                        printf("malloc tmp_s\n");
                        exit(-1);
                }

                len = strlen(res);
                for (u64 i = 0; i < len; i++) {
                        j++;
                        if (res[i] != res[i + 1]) {
                                tmp_s[track++] = (j + '0');
                                tmp_s[track++] = res[i];
                                j = 0;
                        }
                }
                strcpy(res, tmp_s);
                track = 0;
                j = 0;
                free(tmp_s);
        }
        len = strlen(res);

        free(res);

        return len;
}
