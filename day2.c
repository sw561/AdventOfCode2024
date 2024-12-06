#include <stdio.h>
#include <stdlib.h>

void show(int * report, const size_t report_size) {
	for (size_t j = 0; j < report_size; j++) {
		printf("%d ", report[j]);
	}
	printf("\n");
}


int safety(int * report, const size_t report_size)
{
	// Return 0 if unsafe, 1 if safe
	if (report_size < 2) {
		printf("TOO SMALL\n");
		exit(1);
	}
	int increasing = (report[1] - report[0]) > 0;

	for (size_t i = 1; i < report_size; i++) {
		int diff = report[i] - report[i-1];
		if (!(
			(diff > 0) == increasing
				&& abs(diff) > 0
				&& abs(diff) <= 3)
			) return 0;
	}

	// printf("%15s", "Safe version: ");
	// show(report, report_size);

	return 1;
}

int safety_part2(int * report, const size_t report_size, int * workspace)
{
	for (size_t i = 0; i < report_size; i++) {
		// Construct new report with ith entry removed
		for (size_t write_addr = 0; write_addr < report_size-1; write_addr++) {
			workspace[write_addr] = report[write_addr + (write_addr >= i)];
		}
		if (safety(workspace, report_size-1)) {
			return 1;
		}
	}

	return 0;
}

int main()
{
	size_t n = 100;
	char * buffer = malloc(n * sizeof(char));

	int * report = malloc(n * sizeof(int));
	int * workspace = malloc(n * sizeof(int));

	int count_safe = 0;
	int count_safe_part2 = 0;

	while (getline(&buffer, &n, stdin) > 0) {
		size_t ri = 0;
		char * buf_ptr = buffer;
		int n;
		while (sscanf(buf_ptr, "%d %n", report+ri, &n) > 0) {
			ri += 1;
			buf_ptr += n;
		};

		// printf("%15s", "Original: ");
		// show(report, ri);

		if (safety(report, ri)) {
			count_safe += 1;
			count_safe_part2 += 1;
		} else if (safety_part2(report, ri, workspace)) {
			count_safe_part2 += 1;
		}
		// printf("---------------\n");
	}

	printf("Part 1: %d\n", count_safe);
	printf("Part 2: %d\n", count_safe_part2);

	free(buffer);
	free(report);
	free(workspace);

	return 0;
}
