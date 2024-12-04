#include "misc.h"
#include <regex.h>

void part1(FILE *file);
void part2(FILE *file);

int main(void) {
        FILE *file = fopen("./data/day12.txt", "r");
        part1(file);
}

void part1(FILE *file) {
        regex_t re;
        int ret = regcomp(&re, "[[:digit:]]", 0);
        if (ret) {
                fprintf(stderr, "could not compile regex\n");
                exit(EXIT_FAILURE);
        }
}
