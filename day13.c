#include <stdio.h>
#include <limits.h>

int cheapest(int ax, int ay, int bx, int by, int px, int py)
{

	int price = INT_MAX;

	for (int a_presses=0; a_presses < 100; a_presses++) {
		int x = ax * a_presses;
		int y = ay * a_presses;

		if (x > px) {
			break;
		}

		// Calculate number of b presses required
		if ((px - x) % bx == 0) {
			int b_presses = (px - x) / bx;

			y += b_presses * by;

			if (y == py) {

				int new_price = a_presses * 3 + b_presses;
				price = new_price < price ? new_price : price;
			}
		}
	}

	return price == INT_MAX ? -1 : price;
}

int main()
{

	int N;
	scanf("%d\n", &N);

	int ax, ay, bx, by, px, py;

	int part1 = 0;

	for (int i=0; i < N; i++) {
		scanf("Button A: X+%d, Y+%d\n", &ax, &ay);
		scanf("Button B: X+%d, Y+%d\n", &bx, &by);
		scanf("Prize: X=%d, Y=%d\n", &px, &py);
		scanf("\n");


		int price = cheapest(ax, ay, bx, by, px, py);
		// printf("%d %d %d %d : %d %d ---> %d\n", ax, ay, bx, by, px, py, price);

		if (price > 0) {
			part1 += price;
		}
	}

	printf("Part 1: %d\n", part1);

	return 0;
}
