#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_string(char * buffer, char * test, size_t n)
{
	// Check if the n chars in test also exist in buffer using scanf
	char c;
	size_t i = 0;
	while (sscanf(buffer+i, "%c", &c) > 0) {
		if (c != test[i]) {
			return 0;
		}
		if (++i == n) break;
	}
	return 1;
}

int main()
{
	size_t n = 0;
	char * buffer = NULL;

	int part1 = 0;
	int part2 = 0;
	int enabled = 1;

	while (getline(&buffer, &n, stdin) > 0) {
		// printf("%s", buffer);

		size_t n = strlen(buffer);

		// printf("n = %ld\n", n);
		for (size_t i = 0; i < n; i++) {
			// printf("%c", buffer[i]);
			char * d = "do()";
			char * dn = "don't()";
			if (match_string(buffer+i, d, strlen(d))) {
				// printf("%s\n", d);
				enabled = 1;
			} else if (match_string(buffer+i, dn, strlen(dn))) {
				// printf("%s\n", dn);
				enabled = 0;
			} else {
				int a=0;
				int b=0;
				char bracket=0;
				int n_read=0;

				int ret = sscanf(buffer + i, "mul(%d,%d%c%n", &a, &b, &bracket, &n_read);

				if (ret == 3 && bracket==')') {
					// for (int ii=0; ii < n_read; ii++) {
					// 	printf("%c", buffer[i+ii]);
					// }
					// printf(" ------- ");

					// printf("a=%d b=%d c=%c\n", a, b, bracket);
					part1 += a * b;
					if (enabled) part2 += a * b;
				}
			}
		}
	}

	printf("Part 1: %d\n", part1);
	printf("Part 2: %d\n", part2);

	free(buffer);
	// free(report);
	// free(workspace);

	return 0;
}

