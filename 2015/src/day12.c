#include "misc.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void part1(FILE *file);
void part2(FILE *file);

char *get_all_file(FILE *file, u32 len);
int sum_numbers(const char *str, u32 i);
int pos_nb_sum(const char *all, u32 *i);
int neg_nb_sum(const char *all, u32 *i);

int main(void) {
        FILE *file = fopen("./data/day12.txt", "r");
        // part1(file);
        // rewind(file);
        part2(file);

        fclose(file);

        return 0;
}

void part1(FILE *file) {
        u32 len = get_file_length(file);

        char all[len];
        for (int i = 0; i < len; i++) {
                all[i] = fgetc(file);
        }

        char tmp;
        int total = 0;
        for (u32 i = 0; i < len; i++) {
                if (isdigit(all[i])) {
                        total += pos_nb_sum(all, &i);
                }
                if (all[i] == '-') {
                        total += neg_nb_sum(all, &i);
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
        for (u32 i = 1; i < len; i++) {
                if (all[i] == '{') {
                        char object[10000] = {0};
                        u32 obj = 0;
                        i32 open = 0, close = 0;
                        int sum = 0;
                        for (u32 j = i;; j++, obj++) {
                                // check for a open curly bracket
                                if (all[j] == '{')
                                        open++;

                                if (isdigit(all[j])) {
                                        // the pointer of 'i' is passed I can
                                        // keep a track
                                        sum += pos_nb_sum(all, &i);
                                }
                                if (all[i] == '-') {
                                        // same thing here
                                        sum += neg_nb_sum(all, &i);
                                }
                                // copy "object" into new array for checking if
                                // there's "red" inside
                                object[obj] = all[j];

                                // check for close curly bracket
                                if (all[j] == '}')
                                        close++;

                                if (open == close) {
                                        break;
                                }
                        }
                        // int check_inside(const char *str, u32 i);
                        // strstr will search for substring "red" in object
                        // string. if it finds it, it will return the str if not
                        // then it returns (null)
                        bool found = strstr(object, "red") ? true : false;
                        if (found) {
                                printf("> found: %s\n\n", object);
                                i += obj - 1;
                                continue;
                        } else {
                                total += sum;
                        }
                }
                if (isdigit(all[i])) {
                        total += pos_nb_sum(all, &i);
                }
                if (all[i] == '-') {
                        total += neg_nb_sum(all, &i);
                }
        }
        printf("total: %d\n", total);
}

int check_inside(const char *str) {
        for (u32 j = 1; j < strlen(str); j++) {
        }

        return 0;
}

int pos_nb_sum(const char *all, u32 *i) {
        int total = 0;
        u32 o = 0;
        char nb[5] = {0};
        for (u32 j = *i; j < *i + 3; j++) {
                if (isdigit(all[j])) {
                        nb[o] = all[j];
                        o++;
                } else
                        break;
        }
        *i += o;

        total += atoi(nb);

        return total;
}

int neg_nb_sum(const char *all, u32 *i) {
        int total = 0;
        u32 o = 0;
        char nb[5] = {0};
        nb[o] = '-';
        o++;
        for (u32 j = *i + 1; j < *i + 3; j++) {
                if (isdigit(all[j])) {
                        nb[o] = all[j];
                        o++;
                } else
                        break;
        }
        *i += o;
        total += atoi(nb);
        return total;
}
