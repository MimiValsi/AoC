#include "misc.h"

typedef struct {
	uint32_t l; // length
	uint32_t w; // width
	uint32_t h; // height
} Dimension;

Dimension box(int32_t *arr);
void initialize(Dimension *dimension);
uint32_t box_surface(Dimension dimension);
uint32_t extra_slack(Dimension dimension);
uint32_t total_paper(uint32_t surface, uint32_t slack);
int32_t *insertion_sort(Dimension dimension);
uint32_t total_ribbon(int32_t *arr);

int main(void)
{
	Dimension dimension;
	initialize(&dimension);
	FILE *file = fopen("data/day2.txt", "r");
	char *line;
	int32_t *nb = NULL;
	uint32_t paper = 0;
	uint32_t ribbon = 0;
	for (int32_t i = 0; i < 1000; i++) {
		line = get_line(file);
		size_t len = strlen(line);
		nb = str_to_int_array(line, len);
		dimension = box(nb);
		uint32_t surface = box_surface(dimension);
		uint32_t slack = extra_slack(dimension);
		paper += total_paper(surface, slack);
		int32_t *arr = insertion_sort(dimension);
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

int32_t *insertion_sort(Dimension dimension)
{
	int32_t *arr = malloc(3 * sizeof(int32_t));
	arr[0] = dimension.w;
	arr[1] = dimension.l;
	arr[2] = dimension.h;

	for (int32_t i = 0; i < 3; i++) {
		int32_t j = i;
		while (j > 0 && arr[j - 1] > arr[j]) {
			int32_t tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
		}
	}
	return arr;
}

uint32_t total_ribbon(int32_t *arr)
{
	uint32_t wrapper = 0, ribbon = 0;

	wrapper = arr[0] * 2 + arr[1] * 2;
	ribbon = arr[0] * arr[1] * arr[2];
	return wrapper + ribbon;
}

uint32_t total_paper(uint32_t surface, uint32_t slack)
{
	return surface + slack;
}

uint32_t extra_slack(Dimension dimension)
{
	int32_t arr[3] = { 0 };
	arr[0] = dimension.l * dimension.w;
	arr[1] = dimension.w * dimension.h;
	arr[2] = dimension.h * dimension.l;
	uint32_t slack = min_elem(arr, 3);

	return slack;
}

uint32_t box_surface(Dimension dimension)
{
	return 2 * dimension.l * dimension.w + 2 * dimension.w * dimension.h +
	       2 * dimension.h * dimension.l;
}

void initialize(Dimension *dimension)
{
	dimension->l = 0;
	dimension->w = 0;
	dimension->h = 0;
}

Dimension box(int32_t *arr)
{
	Dimension dimension;
	dimension.l = arr[0];
	dimension.w = arr[1];
	dimension.h = arr[2];

	return dimension;
}
