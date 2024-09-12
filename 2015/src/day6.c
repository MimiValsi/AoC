#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"

#define NUM_LINES 300

void part1(FILE *file);
void part2(FILE *file);

int main(void)
{
        FILE *file = fopen("data/day6.txt", "r");
        part1(file);
        rewind(file);
        part2(file);
        fclose(file);
        return 0;
}

void
part1(FILE *file)
{
        // count the total light on lights
        u32 total = 0;
        u32 grid[1000][1000] = {0};

        // line value is NULL, memory will be allocated by get_line()
        // remember to free for each line
        char *line = NULL;

        // light_on starts @ -1 to avoid looping when not needed
        // light_on = 0 to shut down the lights
        // and 1 to light them up
        i32 light_on = -1;

        // toggle is only used when true
        bool toggle = false;

        // 0 is for first coordinates, once passed it's value will be 1
        // and once second coordinates passes, it returns to 0
        u32 first_coordinate = 0;

        u32 start_x = 0,
            end_x = 0,
            start_y = 0,
            end_y = 0;

        // token will get value from strtok() to split string by token (a.k.a word)
        char *token = NULL;

        for (u32 i = 0; i < NUM_LINES; i++) {
                line = get_line(file);
                token = strtok(line, " ");
                while (token) {

                        // compare token with "on", "off" and "toggle"
                        if (strcmp(token, "on") == 0) {
                                light_on = 1;
                        }

                        if (strcmp(token, "off") == 0) {
                                light_on = 0;
                        }

                        if (strcmp(token, "toggle") == 0) {
                                toggle = true;
                        }

                        // check for 1st string of coordinates. 'first_coordinate'
                        // check's if it's start location or end location
                        // first_coordinate = 0 for start and 1 for end
                        // atoi will convert from 1st position, digital number, and convert it till
                        // 1st no digital.
                        // before fetching y coordinates, 1st need to check x coordinate
                        // ex: 490,234
                        // token = 490 (',' is not a digit.)
                        // &token[4] = 234 (start at 5th position)
                        // if ex: 90,234
                        // must pass &token[3]
                        if (isdigit(token[0]) && first_coordinate == 0) {
                                start_x = atoi(token);
                                if (start_x >= 0 && start_x <= 9) {
                                        start_y = atoi(&token[2]);
                                } else if (start_x >= 10 && start_x <= 99) {
                                        start_y = atoi(&token[3]);
                                } else if (start_x >= 100 && start_x <= 999) {
                                        start_y = atoi(&token[4]);
                                }
                                first_coordinate = 1;
                        } else if (isdigit(token[0]) && first_coordinate == 1) {
                                end_x = atoi(token);
                                if (end_x >= 0 && end_x <= 9) {
                                        end_y = atoi(&token[2]);
                                } else if (end_x >= 10 && end_x <= 99) {
                                        end_y = atoi(&token[3]);
                                } else if (end_x >= 100 && end_x <= 999) {
                                        end_y = atoi(&token[4]);
                                }
                                first_coordinate = 0;
                        }

                        token = strtok(NULL, " ");
                }

                // switch on the lights
                if (light_on == 1) {
                        for (u32 j = start_x; j <= end_x; j++) {
                                for (u32 o = start_y; o <= end_y; o++) {
                                        grid[j][o] = 1;
                                }
                        }
                }

                // swtich off lights
                if (light_on == 0) {
                        for (u32 j = start_x; j <= end_x; j++) {
                                for (u32 o = start_y; o <= end_y; o++) {
                                        grid[j][o] = 0;
                                }
                        }
                }

                // toggle from start x,y to end x,y
                // and switch on to off and vice versa
                if (toggle) {
                        for (u32 j = start_x; j <= end_x; j++) {
                                for (u32 o = start_y; o <= end_y; o++) {
                                        if (grid[j][o] == 1) {
                                                grid[j][o] = 0;
                                        } else if (grid[j][o] == 0) {
                                                grid[j][o] = 1;
                                        }
                                }
                        }
                }

                light_on = -1;
                toggle = false;
                free(line);
        }

        // count all lights on
        for (u32 i = 0; i < 1000; i++) {
                for (u32 j = 0; j < 1000; j++) {
                        if (grid[i][j]) {
                                total++;
                        }
                }
        }

        printf("total = %d\n", total);
}

void
part2(FILE *file)
{
        i32 grid[1000][1000] = {0};

        // line value is NULL, memory will be allocated by get_line()
        // remember to free for each line
        char *line = NULL;

        // light_on starts @ -1 to avoid looping when not needed
        // light_on = 0 to shut down the lights
        // and 1 to light them up
        i32 light_on = -1;

        // toggle is only used when true
        bool toggle = false;

        // 0 is for first coordinates, once passed it's value will be 1
        // and once second coordinates passes, it returns to 0
        u32 first_coordinate = 0;

        // total brightness for part2
        i32 brightness = 0;

        u32 start_x = 0,
            end_x = 0,
            start_y = 0,
            end_y = 0;

        // token will get value from strtok() to split string by token (a.k.a word)
        char *token = NULL;

        for (u32 i = 0; i < NUM_LINES; i++) {
                line = get_line(file);
                token = strtok(line, " ");
                while (token) {

                        // compare token with "on", "off" and "toggle"
                        if (strcmp(token, "on") == 0) {
                                light_on = 1;
                        }

                        if (strcmp(token, "off") == 0) {
                                light_on = 0;
                        }

                        if (strcmp(token, "toggle") == 0) {
                                toggle = true;
                        }

                        // check for 1st string of coordinates. 'first_coordinate'
                        // check's if it's start location or end location
                        // first_coordinate = 0 for start and 1 for end
                        // atoi will convert from 1st position, digital number, and convert it till
                        // 1st no digital.
                        // before fetching y coordinates, 1st need to check x coordinate
                        // ex: 490,234
                        // token = 490 (',' is not a digit.)
                        // &token[4] = 234 (start at 5th position)
                        // if ex: 90,234
                        // must pass &token[3]
                        if (isdigit(token[0]) && first_coordinate == 0) {
                                start_x = atoi(token);
                                if (start_x >= 0 && start_x <= 9) {
                                        start_y = atoi(&token[2]);
                                } else if (start_x >= 10 && start_x <= 99) {
                                        start_y = atoi(&token[3]);
                                } else if (start_x >= 100 && start_x <= 999) {
                                        start_y = atoi(&token[4]);
                                }
                                first_coordinate = 1;
                        } else if (isdigit(token[0]) && first_coordinate == 1) {
                                end_x = atoi(token);
                                if (end_x >= 0 && end_x <= 9) {
                                        end_y = atoi(&token[2]);
                                } else if (end_x >= 10 && end_x <= 99) {
                                        end_y = atoi(&token[3]);
                                } else if (end_x >= 100 && end_x <= 999) {
                                        end_y = atoi(&token[4]);
                                }
                                first_coordinate = 0;
                        }

                        token = strtok(NULL, " ");
                }

                // switch on the lights
                if (light_on == 1) {
                        for (u32 j = start_x; j <= end_x; j++) {
                                for (u32 o = start_y; o <= end_y; o++) {
                                        grid[j][o]++;
                                }
                        }
                }

                // swtich off lights
                if (light_on == 0) {
                        for (u32 j = start_x; j <= end_x; j++) {
                                for (u32 o = start_y; o <= end_y; o++) {
                                        grid[j][o]--;
                                        if (grid[j][o] < 0) {
                                               grid[j][o] = 0;
                                        }
                                }
                        }
                }

                // toggle from start x,y to end x,y
                // and switch on to off and vice versa
                if (toggle) {
                        for (u32 j = start_x; j <= end_x; j++) {
                                for (u32 o = start_y; o <= end_y; o++) {
                                        grid[j][o] += 2;
                                }
                        }
                }

                light_on = -1;
                toggle = false;
                free(line);
        }

        // count all lights on
        for (u32 i = 0; i < 1000; i++) {
                for (u32 j = 0; j < 1000; j++) {
                        brightness += grid[i][j];
                }
        }
        printf("brightness = %d\n", brightness);
}
