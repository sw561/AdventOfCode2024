#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#ifdef TEST
#define NROWS 7
#define NCOLS 11
#else
#define NROWS 103
#define NCOLS 101
#endif

typedef struct robot {
	int px,py,vx,vy;
} robot;

typedef struct state {
	int n_robots;
	robot * robots;
	int updates;
} state;

void display(state * s, int * robot_counts) {

	static bool started_print = false;
	if (started_print) {
		printf("[%dA\r[0J", NROWS+1);
	}
	started_print = true;

	memset(robot_counts, 0, NROWS*NCOLS*sizeof(int));

	for (int i=0; i < s->n_robots; i++) {
		int index = NCOLS * s->robots[i].py + s->robots[i].px;
		if (index < 0 || index >= NROWS * NCOLS) {
			printf("ERROR (px,py) = (%d,%d) index=%d, NROWS=%d, NCOLS=%d, NROWS*NCOLS=%d\n",
				s->robots[i].px, s->robots[i].py, index, NROWS, NCOLS, NROWS*NCOLS);
			exit(1);
		}
		robot_counts[index]++;
	}

	printf("N updates: %d\n", s->updates);

	for (int row=0; row < NROWS; row++) {
		for (int col=0; col < NCOLS; col++) {
			int c = robot_counts[NCOLS * row + col];
			if (c) {
				printf("%d", c);
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}

void update_all(state * s) {
	for (int i=0; i < s->n_robots; i++) {
		s->robots[i].px += s->robots[i].vx;
		s->robots[i].py += s->robots[i].vy;
		while (s->robots[i].px < 0) {
			s->robots[i].px += NCOLS;
		}
		while (s->robots[i].py < 0) {
			s->robots[i].py += NROWS;
		}
		s->robots[i].px %= NCOLS;
		s->robots[i].py %= NROWS;
	}
	s->updates++;
}

int main()
{
	state s = {
		.n_robots = 0,
		.robots = malloc(500 * sizeof(robot)),
		.updates = 0
	};

	// int n_robots = 0;
	// robot * robots = malloc(500 * sizeof(robot));

	int * workspace = malloc(NROWS * NCOLS * sizeof(int));

	size_t n;
	char * buffer;
	while (getline(&buffer, &n, stdin) > 0) {
		sscanf(buffer, "p=%d,%d v=%d,%d",
			&s.robots[s.n_robots].px,
			&s.robots[s.n_robots].py,
			&s.robots[s.n_robots].vx,
			&s.robots[s.n_robots].vy);

		s.n_robots++;
	}
	free(buffer);

	// for (int i=0; i < s.n_robots; i++) {
	// 	printf("(%d,%d) (%d,%d)\n",
	// 		s.robots[i].px,
	// 		s.robots[i].py,
	// 		s.robots[i].vx,
	// 		s.robots[i].vy);
	// }

	// display(&s, workspace);

	// for (; updates < 100; updates++) {
	while (s.updates < 100)
		update_all(&s);
	// }
	// display(&s, workspace);

	// Count quadrants

	int tl = 0;
	int tr = 0;
	int bl = 0;
	int br = 0;

	for (int i=0; i < s.n_robots; i++) {
		if (s.robots[i].py < NROWS / 2) {
			if (s.robots[i].px < NCOLS / 2) {
				tl++;
			} else if (s.robots[i].px > NCOLS / 2) {
				tr++;
			}
		} else if (s.robots[i].py > NROWS / 2) {
			if (s.robots[i].px < NCOLS / 2) {
				bl++;
			} else if (s.robots[i].px > NCOLS / 2) {
				br++;
			}
		}
	}

	// printf("%d,%d,%d,%d\n",tl,tr,bl,br);

	int part1 = tl * tr * bl * br;
	printf("Part 1: %d\n", part1);

	free(s.robots);
	free(workspace);

	return 0;
}
