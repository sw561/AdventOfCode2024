#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare( const void* a, const void* b)
{
	int int_a = * ( (int*) a );
	int int_b = * ( (int*) b );

	if ( int_a == int_b ) return 0;
	else if ( int_a < int_b ) return -1;
	else return 1;
}

#define N 1000

int main(){
	int * a = malloc(N * sizeof(int));
	int * b = malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) {
		int x = 0;
		int y = 0;
		scanf("%d %d\n", &x, &y);
		a[i] = x;
		b[i] = y;
	}
	qsort(a, N, sizeof(int), compare);
	qsort(b, N, sizeof(int), compare);
	int diff = 0;
	for (int i=0; i < N; i++) {
		diff += abs(a[i] - b[i]);
	}
	printf("Part 1: %d\n", diff);

	// Count number of occurences of each left side number in right side
	// c[i] will be count of occurrences of a[i] in b[i]
	int * c = calloc(N, sizeof(int));

	int ai = 0;
	int bi = 0;
	while (ai < N && bi < N) {
		if (a[ai] == b[bi]) {
			c[ai] += 1;
			bi += 1;
		} else if (a[ai] < b[bi]) {
			ai += 1;
			if (ai < N && a[ai] == a[ai-1]) {
				c[ai] = c[ai-1];
			}
		} else if (a[ai] > b[bi]) {
			bi += 1;
		}
	}

	int total = 0;
	for (int i = 0; i < N; i++) {
		total += a[i] * c[i];
	}

	printf("Part 2: %d\n", total);

	free(a);
	free(b);
	free(c);
}
