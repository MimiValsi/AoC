#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "misc.h"

#define LINES_NUM 1000

int part1(FILE *file);
int part2(FILE *file);
bool check_vowels(char *line, u32 len);
bool check_double_letter(char *line, u32 len);
bool check_naughty_letters(char *line, u32 len);
bool no_overlap(char *line, u32 len);
bool repeating(char *line, u32 len);

int main(void)
{
        FILE *file = fopen("data/day5.txt", "r");
        part1(file);

        // Need to rewind to file start to avoid segmented fault
        // so part2 can work properly
        rewind(file);
        part2(file);
        fclose(file);
}

int
part1(FILE *file)
{
        char *line = get_line(file);
        u32 len = strlen(line);
        u32 c = 0;
        rewind(file);
        free(line);

        // Loop iterate over each file line
        for (u32 i = 0; i < LINES_NUM; i++) {
                line = get_line(file);
                if (
                        check_vowels(line, len) &&
                        check_double_letter(line, len) &&
                        check_naughty_letters(line, len)
                ) {
                        c++;
                }
                free(line);
        }
        printf("%d\n", c);
        return 0;
}


bool
check_vowels(char *line, u32 len)
{
        char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
        u8 c = 0;

        // Loop iterate over each char/char line
        for (u32 i = 0; i < len; i++) {
                // Loop iterate to check if there's any vowels and how many are present
                for (u32 j = 0; j < 5; j++) {
                        if (line[i] == vowels[j]) {
                                c++;
                        }
                }
        }
        if (c >= 3) {
                return true;
        }

        return false;
}

bool
check_double_letter(char *line, u32 len)
{
        u8 c = 0;
        for (u32 i = 0; i < len-1; i++) {
                if (line[i] == line[i+1]) {
                        c++;
                }
        }
        if (c >= 1) {
                return true;
        }
        return false;
}

bool
check_naughty_letters(char *line, u32 len)
{
        const char *naughty[4] = {"ab", "cd", "pq", "xy"};
        char buf[3] = {0};
        u8 c = 0;
        for (u32 i = 0; i < len-1; i++) {
                buf[0] = line[i];
                buf[1] = line[i+1];
                for (u32 j = 0; j < 4; j++) {
                        if (strcmp(naughty[j], buf) == 0) {
                                c++;
                        }
                }
        }
        if (c == 0) {
                return true;
        }
        return false;
}

int
part2(FILE *file)
{
        char *line = get_line(file);
        u32 len = strlen(line);
        u32 c = 0;
        rewind(file);
        free(line);
        // Loop iterate over each file line
        for (u32 i = 0; i < LINES_NUM; i++) {
                line = get_line(file);
                if (
                no_overlap(line, len) &&
                repeating(line, len)
                ) {
                        c++;
                }
                free(line);
        }
        printf("%d\n", c);
        return 0;
}

bool
no_overlap(char *line, u32 len)
{
        char buf[3] = {0};
        char tmp[3] = {0};

        for (u32 i = 0; i < len; i++) {
                buf[0] = line[i];
                buf[1] = line[i+1];
                for (u32 j = i+2; j < len; j++) {
                        tmp[0] = line[j];
                        tmp[1] = line[j+1];
                        if (strcmp(buf, tmp) == 0) {
                                return true;
                        }
                }
        }

        return false;
}

bool
repeating(char *line, u32 len)
{
        for (u32 i = 0; i < len-2; i++) {
                if (line[i] == line[i+2]) {
                        return true;
                }
        }
        return false;
}
