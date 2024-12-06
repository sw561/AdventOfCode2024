#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Point {
	int i, j;
} Point;

int detect_infinite_loop(const char ** map, int N,
		int ** visited, Point pos, Point dir
	){

	int count_visited = 0;

	for (int i=0; i < N; i++) {
		memset(visited[i], 0, N * sizeof(int));
	}

	while (1) {
		if (!visited[pos.i][pos.j]) {
			count_visited++;
		}

		int m;
		// Map directions to numbers so we can store direction of previous visits
		// as a bit in the visited int
		if (dir.i == -1) {
			m = 1;
		} else if (dir.i == 1) {
			m = 1 << 1;
		} else if (dir.j == -1) {
			m = 1 << 2;
		} else if (dir.j == +1) {
			m = 1 << 3;
		} else {
			assert(0 && "STOP");
		}

		if (visited[pos.i][pos.j] & m) {
			// Infinite loop detected
			return -1;
		}
		visited[pos.i][pos.j] |= m;

		pos.i += dir.i;
		pos.j += dir.j;

		if (!(0 <= pos.i && pos.i < N && 0 <= pos.j && pos.j < N)) {
			return count_visited;
		}

		if (map[pos.i][pos.j] == '#') {
			// Take a step back and change direction
			pos.i -= dir.i;
			pos.j -= dir.j;

			// Turn 90 degrees
			// -1,0 -> 0, 1
			// 0, 1 -> 1, 0
			// 1, 0 -> 0, -1
			// 0, -1 -> -1, 0

			int temp = dir.i;
			dir.i = dir.j;
			dir.j = -temp;
		}

	}
}

int main()
{
	int N;
	scanf("%d\n", &N);

	char ** map = calloc(N, sizeof (char*));
	int ** visited = malloc(N * sizeof (int*));
	int ** visited2 = malloc(N * sizeof (int*));
	for (int i=0; i < N; i++) {
		visited[i] = malloc(N * sizeof(int));
		visited2[i] = malloc(N * sizeof(int));
	}

	Point pos = {0};
	Point dir = {0};

	for (int i=0; i < N; i++) {
		size_t n;
		getline(&map[i], &n, stdin);
		n = strlen(map[i]);
		// printf("%s", map[i]);
		// printf("N=%d n = %ld\n", N, n);
		assert((int)n == N+1);

		for (int j = 0; j < N; j++) {
			if (map[i][j] == '^') {
				pos = (Point) {.i = i, .j = j};
				dir = (Point) {.i = -1, .j = 0};
			}
		}
	}

	assert(pos.i != 0);
	assert(pos.j != 0);

	int ret = detect_infinite_loop(
		(const char **)map, N, visited, pos, dir
		);

	printf("Part 1: %d\n", ret);
	// printf("infinite loop: %d\n", r.infinite_loop);

	int count_infinite_loop_obstacles = 0;
	for (int i=0; i < N; i++) {
		for (int j=0; j < N; j++) {
			if (map[i][j] == '.' && visited[i][j]) {
				map[i][j] = '#';

				int ret = detect_infinite_loop(
					(const char **)map, N, visited2, pos, dir
					);

				count_infinite_loop_obstacles += (ret < 0);
				map[i][j] = '.';
			}
		}
	}

	printf("Part 2: %d\n", count_infinite_loop_obstacles);

	for (int i=0; i < N; i++) {
		free(map[i]);
		free(visited[i]);
		free(visited2[i]);
	}
	free(map);
	free(visited);
	free(visited2);

	return 0;
}
