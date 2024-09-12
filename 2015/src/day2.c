#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"

typedef struct {
        u32 l; // length
        u32 w; // width
        u32 h; // height
} Dimension;

Dimension box(i32 *arr);
void initialize(Dimension *dimension);
u32 box_surface(Dimension dimension);
u32 extra_slack(Dimension dimension);
u32 total_paper(u32 surface, u32 slack);
i32* insertion_sort(Dimension dimension);
u32 total_ribbon(i32 *arr);

int main(void)
{
        Dimension dimension;
        initialize(&dimension);
        FILE *file = fopen("data/day2.txt", "r");
        char *line;
        i32 *nb = NULL;
        u32 paper = 0;
        u32 ribbon = 0;
        for (i32 i = 0; i < 1000; i++) {
                line = get_line(file);
                size_t len = strlen(line);
                nb = str_to_int_array(line, len);
                dimension = box(nb);
                u32 surface = box_surface(dimension);
                u32 slack = extra_slack(dimension);
                paper += total_paper(surface, slack);
                i32 *arr = insertion_sort(dimension);
                ribbon += total_ribbon(arr);

                free(line);
                free(nb);
                free(arr);
        }

        printf("%d\n", paper);
        printf("%d\n", ribbon);

        fclose(file);
        return 0;
}

i32*
insertion_sort(Dimension dimension)
{
        i32 *arr = malloc(3 * sizeof(i32));
        arr[0] = dimension.w;
        arr[1] = dimension.l;
        arr[2] = dimension.h;

        for (i32 i = 0; i < 3; i++) {
                i32 j = i;
                while (j > 0 && arr[j - 1] > arr[j]) {
                        i32 tmp = arr[j - 1];
                        arr[j - 1] = arr[j];
                        arr[j] = tmp;
                }
        }
        return arr;
}

u32
total_ribbon(i32 *arr)
{
        u32 wrapper = 0,
        ribbon = 0;

        wrapper = arr[0]*2 + arr[1]*2;
        ribbon = arr[0] * arr[1] * arr[2];
        return wrapper + ribbon;
}

u32
total_paper(u32 surface, u32 slack)
{
        return surface + slack;
}

u32
extra_slack(Dimension dimension)
{
        i32 arr[3] = {0};
        arr[0] = dimension.l * dimension.w;
        arr[1] = dimension.w * dimension.h;
        arr[2] = dimension.h * dimension.l;
        u32 slack = min_elem(arr, 3);

        return slack;
}

u32
box_surface(Dimension dimension)
{
        return 2*dimension.l*dimension.w + 2*dimension.w*dimension.h + 2*dimension.h*dimension.l;
}

void
initialize(Dimension *dimension)
{
        dimension->l = 0;
        dimension->w = 0;
        dimension->h = 0;
}

Dimension
box(i32 *arr)
{
        Dimension dimension;
        dimension.l = arr[0];
        dimension.w = arr[1];
        dimension.h = arr[2];

        return dimension;
}
