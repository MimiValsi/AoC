#include "misc.h"

void part1(FILE *file);
void part2(FILE *file);

char *get_all_file(FILE *file, u32 len);

int main(void) {
        FILE *file = fopen("./data/day12.txt", "r");
        part1(file);
        rewind(file);
        part2(file);

        fclose(file);
}

void part1(FILE *file) {
        char string[100] = {0};
        u32 len = get_file_length(file);

        char all[len];
        for (int i = 0; i < len; i++) {
                all[i] = fgetc(file);
        }

        char tmp;
        int total = 0;
        for (u32 i = 0; i < len; i++) {
                if (isdigit(all[i])) {
                        u32 o = 0;
                        char nb[5] = {0};
                        for (u32 j = i; j < i + 3; j++) {
                                if (isdigit(all[j])) {
                                        nb[o] = all[j];
                                        o++;
                                } else
                                        break;
                        }
                        i += o;
                        total += atoi(nb);
                }
                if (all[i] == '-') {
                        u32 o = 0;
                        char nb[5] = {0};
                        nb[o] = '-';
                        o++;
                        for (u32 j = i + 1; j < i + 3; j++) {
                                if (isdigit(all[j])) {
                                        nb[o] = all[j];
                                        o++;
                                } else
                                        break;
                        }
                        i += o;
                        total += atoi(nb);
                }
        }
        printf("total: %d\n", total);
}

void part2(FILE *file) {
        char string[100] = {0};
        u32 len = get_file_length(file);

        char all[len];
        for (int i = 0; i < len; i++) {
                all[i] = fgetc(file);
        }

        char tmp;
        int total = 0;
        for (u32 i = 0; i < len; i++) {
                if (isdigit(all[i])) {
                        u32 o = 0;
                        char nb[5] = {0};
                        for (u32 j = i; j < i + 3; j++) {
                                if (isdigit(all[j])) {
                                        nb[o] = all[j];
                                        o++;
                                } else
                                        break;
                        }
                        i += o;
                        total += atoi(nb);
                }
                if (all[i] == '-') {
                        u32 o = 0;
                        char nb[5] = {0};
                        nb[o] = '-';
                        o++;
                        for (u32 j = i + 1; j < i + 3; j++) {
                                if (isdigit(all[j])) {
                                        nb[o] = all[j];
                                        o++;
                                } else
                                        break;
                        }
                        i += o;
                        total += atoi(nb);
                }
        }
        printf("total: %d\n", total);
}
