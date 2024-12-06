#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int valid(int i, int j, int N)
{
	return i >= 0 && i < N && j >= 0 && j < N;
}

int find_xmas(char ** wordsearch, int i, int j, int dx, int dy, int N) {
	char * xmas = "XMAS";

	for (int d = 0; d < 4; d++) {
		if (!valid(i, j, N)) return 0;

		if (wordsearch[i][j] != xmas[d]) return 0;

		i += dx;
		j += dy;
	}
	return 1;
}


int find_x_mas(char ** wordsearch, int i, int j, int dx, int dy, int N) {
	char * c = "MAS";
	int x_steps[] = {0, 1, 2};
	int y_steps[] = {0, 1, 2};
	for (int d = 0; d < 3; d++) {
		int ci = i + dx * x_steps[d];
		int cj = j + dy * y_steps[d];

		if (!valid(ci, cj, N)) return 0;

		if (wordsearch[ci][cj] != c[d]) return 0;
	}

	// On the opposite corners we need one M and one S
	// Opposite corners are
	int ci = i + 2 * dx;
	int cj = j;

	int cci = i;
	int ccj = j + 2 * dy;
	switch (wordsearch[ci][cj]) {
		case 'M':
			return wordsearch[cci][ccj] == 'S';
		case 'S':
			return wordsearch[cci][ccj] == 'M';
		default:
			return 0;
	}
}

int main()
{

	int N;
	scanf("%d\n", &N);

	char ** wordsearch = calloc(N, sizeof (char*));

	for (int i=0; i < N; i++) {
		size_t n;
		getline(&wordsearch[i], &n, stdin);
		n = strlen(wordsearch[i]);
		// printf("%s", wordsearch[i]);
		// printf("N=%d n = %ld\n", N, n);
		assert((int)n == N+1);
	}

	// for (int i=0; i < N; i++) {
	// 	for (int j = 0; j < N; j++) {
	// 		printf("%c", wordsearch[i][j]);
	// 	}
	// 	printf("\n");
	// }

	int part1 = 0;
	int part2 = 0;
	for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
		for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0) continue;
			part1 += find_xmas(wordsearch, i, j, dx, dy, N);

			if (dx == 0 || dy == 0) continue;
			part2 += find_x_mas(wordsearch, i, j, dx, dy, N);
			// printf("-------\n");
		}}
	}}

	printf("Part1: %d\n", part1);
	printf("Part2: %d\n", part2 / 2);

	return 0;
}
