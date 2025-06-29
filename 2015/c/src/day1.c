#include "misc.h"

int main(void)
{
	FILE *file = fopen("data/day1.txt", "r");
        
	int32_t floor = 0, position = 0;
	uint64_t end = get_file_length(file);

	for (uint64_t i = 0; i < end; i++) {
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
