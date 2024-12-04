#include "misc.h"
#include <stdio.h>

void part1(char *puzzle);
void part2(char *puzzle);

void check_string(char *puzzle, u32 len, i32 i);
bool straight_three_letters(char *puzzle, u32 len);
bool no_i_o_l(char *puzzle, u32 len);
bool overlap(char *puzzle, u32 len);

int main() {
        char puzzle[] = "hepxcrrq"; // hepxxyzz

        part1(puzzle);
        part2(puzzle);
}

void part1(char *puzzle) {
        printf("start: %s\n", puzzle);
        u32 len = strlen(puzzle);

        // Loop will break when all requirements are meet
        i32 i;
        u32 j = 0;
        for (;;) {
                i = len - 1;
                bool straight_3_letters = false;
                bool no_iol = false;
                bool overlaps = false;
                if (straight_three_letters(puzzle, len)) {
                        straight_3_letters = true;
                }
                if (no_i_o_l(puzzle, len)) {
                        no_iol = true;
                }
                if (overlap(puzzle, len)) {
                        overlaps = true;
                }

                if (straight_3_letters && no_iol && overlaps) {
                        break;
                }

                ++puzzle[i];
        }
        printf("end: %s\n", puzzle);
}

// check each char of the string. If puzzle[i] == 'z' then the previous char
// will shift to next letter and puzzle[i] restart @ a
void check_string(char *puzzle, u32 len, i32 i) {
        if (puzzle[i] == 'z') {
                puzzle[i] = 'a';
                check_string(puzzle, len, --i);
        } else {
                puzzle[i]++;
                return;
        }
}

bool straight_three_letters(char *puzzle, u32 len) {
        for (u32 i = 0; i < len; i++) {
                bool tmp_1 = ((puzzle[i] + 1 == puzzle[i + 1]) &&
                              (puzzle[i] + 2 == puzzle[i + 2]));
                if (tmp_1)
                        return true;
        }

        return false;
}

// easiest one.
// check if there's the letters 'i', 'o' or 'l'
// if so, then return false
bool no_i_o_l(char *puzzle, u32 len) {
        for (u32 i = 0; i < len; i++) {
                if (puzzle[i] == 'i' || puzzle[i] == 'o' || puzzle[i] == 'l')
                        return false;
        }

        return true;
}

// trick check.
// It checks if there's a sequence of the same letter.
// and if there's no overlap
// Exemple: aabcc (It seems this is valid)
// aabbb
// this would be overlapping...(?)
bool overlap(char *puzzle, u32 len) {
        int count = 0;
        for (u32 i = 0; i < len; i++) {
                bool pair =
                    puzzle[i] == puzzle[i + 1] && puzzle[i] != puzzle[i + 2];
                if (pair) {
                        count++;
                        if (i < len) {
                                for (u32 j = i + 1; j < len; j++) {
                                        if (puzzle[j] == puzzle[j + 1]) {
                                                count++;
                                        }
                                }
                        }
                }
                if (count == 2) {
                        return true;
                }
        }

        return false;
}

void part2(char *puzzle) {
        printf("start: %s\n", puzzle);
        u32 len = strlen(puzzle);

        // Loop will break when all requirements are meet
        i32 i;
        u32 j = 0;
        for (;;) {
                i = len - 1;
                bool straight_3_letters = false;
                bool no_iol = false;
                bool overlaps = false;
                if (puzzle[i] == 'z') {
                        // if last letter is z increment previous letter to next
                        // one
                        check_string(puzzle, len, i);
                }
                if (straight_three_letters(puzzle, len)) {
                        straight_3_letters = true;
                }
                if (no_i_o_l(puzzle, len)) {
                        no_iol = true;
                }
                if (overlap(puzzle, len)) {
                        overlaps = true;
                }

                if (straight_3_letters && no_iol && overlaps) {
                        break;
                }

                ++puzzle[i];
        }
        printf("end: %s\n", puzzle);
}
