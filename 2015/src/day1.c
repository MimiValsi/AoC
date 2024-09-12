#include <stdio.h>
#include "misc.h"

int
main(void)
{
        FILE *file = fopen("data/day1.txt", "r");

        i32 floor = 0, position = 0;
        u64 end = get_file_length(file);

        for (u64 i = 0; i < end; i++) {
                position++;
                if (fgetc(file) == '(') {
                        floor++;
                } else {
                        floor--;
                }

                if (floor == -1) {
                        printf("%d\n", position);
                }

        }

        printf("floor: %d\n", floor);
        fclose(file);
        return 0;
}
