#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Point {
	int i, j;
} Point;

typedef struct Array2D {
	int * data;
	int N, M;
} Array2D;

Array2D allocate_2D(int N, int M)
{
	return (Array2D) {
		.data = malloc(N * M * sizeof(int*)),
		.N = N,
		.M = M
		};
}

int valid(Array2D a, Point p)
{
	return (0 <= p.i && p.i < a.N && 0 <= p.j && p.j < a.M);
}

int * get(Array2D a, Point p)
{
	return &a.data[p.i * a.N + p.j];
}

void set_all(Array2D * a, int x)
{
	memset(a->data, x, a->N * a->M * sizeof(int));
}

void free_2D(Array2D a) {
	free(a.data);
}

int detect_infinite_loop(const char ** map,
		Array2D visited, Point pos, Point dir
	){

	int count_visited = 0;

	set_all(&visited, 0);

	while (1) {
		if (!*get(visited, pos)) {
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

		if (*get(visited, pos) & m) {
			// Infinite loop detected
			return -1;
		}
		*get(visited, pos) |= m;

		pos.i += dir.i;
		pos.j += dir.j;

		if (!valid(visited, pos)) {
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
	Array2D visited = allocate_2D(N, N);
	Array2D visited2 = allocate_2D(N, N);

	Point pos = {0};
	Point dir = {0};

	for (int i=0; i < N; i++) {
		size_t n;
		getline(&map[i], &n, stdin);
		n = strlen(map[i]);
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
		(const char **)map, visited, pos, dir
		);

	printf("Part 1: %d\n", ret);
	// printf("infinite loop: %d\n", r.infinite_loop);

	int count_infinite_loop_obstacles = 0;
	for (int i=0; i < N; i++) {
		for (int j=0; j < N; j++) {
			if (map[i][j] == '.' && *get(visited, (Point) {.i=i, .j=j} )) {
				map[i][j] = '#';

				int ret = detect_infinite_loop(
					(const char **)map, visited2, pos, dir
					);

				count_infinite_loop_obstacles += (ret < 0);
				map[i][j] = '.';
			}
		}
	}

	printf("Part 2: %d\n", count_infinite_loop_obstacles);

	for (int i=0; i < N; i++) {
		free(map[i]);
	}
	free(map);
	free_2D(visited);
	free_2D(visited2);

	return 0;
}
