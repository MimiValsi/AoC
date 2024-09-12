#include "misc.h"

// uncomment either 1st for test.txt or 2nd to day8.txt
// #define NB_LINES 4
// #define OPENFILE fopen("data/test.txt", "r")

#define NB_LINES 300
#define OPENFILE fopen("data/day8.txt", "r")

// arbitrary number
#define NEW_ARR_LEN 100

u32 part1(FILE *file);
u32 part2(FILE *file);
u32 nb_chars_code(char const *str);
u32 nb_chars_string(char const *str);
u32 new_chars_str(char const *str);

int main(void)
{
        FILE *file = OPENFILE;

        u32 p1 = part1(file);
        rewind(file);
        u32 p2 = part2(file);
        fclose(file);
        printf("part1: %d\n", p1);
        printf("part2: %d\n", p2);
        return 0;
}

u32
part1(FILE *file)
{
        /* ""           <- 2 chars of code  / 0 char of string
         * "abc"        <- 5 chars of code  / 3 chars of string
         * "aaa\"aaa"   <- 10 chars of code / 7 chars of string
         * "\x27"       <- 6 chars of code  / 1 char of string
         *
         * 3 escape sequeces:
         * \\ <- \
         * \" <- "
         * \x <- add 2 hex chars
         */
        u32 chars_code = 0;
        u32 chars_str = 0;
        for (int i = 0; i < NB_LINES; i++) {
                char *line = get_line(file);
                chars_code += nb_chars_code(line);
                chars_str += nb_chars_string(line);
                free(line);
        }

        // printf("chars: %d\n", chars_code);
        return chars_code - chars_str;

}

// count every char in the string
u32
nb_chars_code(char const *str)
{
        u32 sum = 0;
        u32 len = strlen(str);
        for (int i = 0; i < len; i++) {
                sum++;
        }

        return sum;
}

// skip first and last double quote of the string,
// when \ and " are the 2 next chars so it can be count once
// when \ and x are the 2 next chars so i is incremented twice so that \x27 is only counted once (i is incremented by 3)
// when double \ is next increment i once and add sum (i is increment by 2)
u32
nb_chars_string(char const *str)
{
        u32 sum = 0;
        u32 len = strlen(str);
        for (int i = 0; i < len; i++) {
                if (str[i] == '"' && (i == 0 || i == len-1)) {
                        continue;
                }
                if (str[i] == '\\' && str[i+1] == '"') {
                        continue;
                }
                if (str[i] == '\\' && str[i+1] == 'x') {
                        i+=2;
                        continue;
                }
                if (str[i] == '\\' && str[i+1] == '\\') {
                        i++;
                        sum++;
                        continue;
                }

                sum++;
        }

        return sum;
}

u32
part2(FILE *file)
{
        /* ""         -> "\"\""             <- 2 chars of code  / 6 new chars of string
         * "abc"      -> "\"abc\""          <- 5 chars of code  / 9 chars of string
         * "aaa\"aaa" -> "\"aaa\\\"aaa\""   <- 10 chars of code / 16 chars of string
         * "\x27"     -> "\"\\x27\""        <- 6 chars of code  / 11 char of string
         *
         * 3 escape sequeces:
         * "" 1st and last -> "\"\""  <- add 4 pts for each string
         * \" -> \\                   <- add 2 pts
         * \x -> \                    <- add 1 pt
         */
        char new_str[NEW_ARR_LEN] = {0};
        u32 chars_str_new = 0;
        u32 chars_code = 0;
        for (int i = 0; i < NB_LINES; i++) {
                char *line = get_line(file);

                chars_code += nb_chars_code(line);
                chars_str_new += new_chars_str(line);

                free(line);
        }
        return chars_str_new - chars_code;

}

u32
new_chars_str(char const *str)
{
        u32 len = strlen(str);
        u32 sum = 0;

        char new[NEW_ARR_LEN] = {0};
        u32 j = 2;
        new[0] = '"';
        new[1] = '\\';
        for (int i = 0; i < len-1; i++) {
                /*
                 * add 1 backslash only if it's a hex digit
                 *
                 */
                if (str[i] == '\\' && str[i+1] == 'x' && isxdigit(str[i+2]) && isxdigit(str[i+3])) {
                        new[j] = str[i];
                        new[j+1] = '\\';
                        j+=2;
                        continue;
                }

                /*
                 * add 2 more backslash plus the next char. skip 1 more 'i' iteration
                 * it doesn't matter which chars comes after \
                 *
                 */
                if (str[i] == '\\') {
                        new[j] = str[i];
                        new[j+1] = '\\';
                        new[j+2] = '\\';
                        new[j+3] = str[i+1];
                        j+=4;
                        i++;
                        continue;
                }

                new[j] = str[i];
                j++;
        }
        new[j] = '\\';
        new[j+1] = '"';
        new[j+2] = '"';
        for (int i = 0; i < strlen(new); i++) {
                sum++;
        }

        return sum;
}
