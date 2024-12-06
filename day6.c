#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Point {
	int i, j;
} Point;

int valid(Point * p, int N)
{
	return p->i >= 0 && p->i < N && p->j >= 0 && p->j < N;
}

int move(const char ** map, int N, Point * p, Point * d)
{
	p->i += d->i;
	p->j += d->j;

	if (!valid(p, N)) {
		return 1;
	}

	if (map[p->i][p->j] == '#') {
		// Take a step back and change direction
		p->i -= d->i;
		p->j -= d->j;

		// Turn 90 degrees
		// -1,0 -> 0, 1
		// 0, 1 -> 1, 0
		// 1, 0 -> 0, -1
		// 0, -1 -> -1, 0

		int temp = d->i;
		d->i = d->j;
		d->j = -temp;
	}

	return 0;
}

int map_dir(Point * d) {
	// Map directions to numbers so we can store direction of previous visits
	// as a bit in the visited int
	if (d->i == -1 && d->j == 0) {
		return 1;
	} else if (d->i == 0 && d->j == 1) {
		return 1 << 1;
	} else if (d->i == 1 && d->j == 0) {
		return 1 << 2;
	} else if (d->i == 0 && d->j == -1) {
		return 1 << 3;
	} else {
		assert(0 && "STOP");
	}
}

struct rettype {
	int count_visited, infinite_loop;
};

struct rettype detect_infinite_loop(const char ** map, int N, int ** visited, Point pos, Point dir){

	int count_visited = 0;
	int infinite_loop = 0;

	for (int i=0; i < N; i++) {
		memset(visited[i], 0, N * sizeof(int));
	}

	do {
		if (!visited[pos.i][pos.j]) {
			count_visited++;
		}
		int m = map_dir(&dir);
		if (visited[pos.i][pos.j] & m) {
			infinite_loop = 1;
			break;
		}
		visited[pos.i][pos.j] |= m;
	} while (!move(map, N, &pos, &dir));

	// if (infinite_loop) {
	// 	for (int i=0; i < N; i++) {
	// 		for (int j = 0; j < N; j++) {
	// 			if (visited[i][j] != 0) {
	// 				printf("X");
	// 				// printf("%d", visited[i][j]);
	// 			} else {
	// 				printf("%c", map[i][j]);
	// 			}
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("----------------------\n");
	// }

	return (struct rettype) {
		.count_visited = count_visited,
		.infinite_loop = infinite_loop
		};
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

	struct rettype r = detect_infinite_loop(
		(const char **)map, N, visited, pos, dir
		);

	printf("Part 1: %d\n", r.count_visited);
	// printf("infinite loop: %d\n", r.infinite_loop);

	int count_infinite_loop_obstacles = 0;
	for (int i=0; i < N; i++) {
		for (int j=0; j < N; j++) {
			if (map[i][j] == '.' && visited[i][j]) {
				map[i][j] = '#';

				struct rettype r = detect_infinite_loop(
					(const char **)map, N, visited2, pos, dir
					);

				count_infinite_loop_obstacles += r.infinite_loop;
				map[i][j] = '.';
			}
		}
	}

	printf("Part 2: %d\n", count_infinite_loop_obstacles);

	return 0;
}
