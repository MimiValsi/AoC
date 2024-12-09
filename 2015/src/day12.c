#include "misc.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(FILE *file);
void part2(FILE *file);

char *get_all_file(FILE *file, u32 len);
int sum_numbers(const char *str, u32 i);
int pos_nb_sum(const char *all, u32 *i);
int neg_nb_sum(const char *all, u32 *i);
void zero_arr(char *arr);

int main(void) {
        // FILE *file = fopen("./data/day12.txt", "r");
        FILE *file = fopen("./data/day12_2.txt", "r");
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

int foo(const char *str) {
        u32 len = strlen(str);
        int obj = 0, total = 0, t = 0;
        char tmp[1000] = {0};
        bool b[100] = {0};

        for (u32 i = 0; i < len; i++) {
                if (str[i] == '{') {
                        bool found = strstr(tmp, "red") ? true : false;
                        if (found) {
                                t = 0;
                                zero_arr(tmp);
                        }
                        obj++;
                }

                tmp[t] = str[i];
                t++;
                if (isdigit(str[i])) {
                        total += pos_nb_sum(str, &i);
                }
                if (str[i] == '-') {
                        total += neg_nb_sum(str, &i);
                }

                if (str[i] == '}') {
                        obj--;
                        t = 0;
                }
        }

        return 0;
}

void zero_arr(char *arr) {
        for (int i = 0; i < strlen(arr); i++) {
                arr[i] = 0;
        }
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
