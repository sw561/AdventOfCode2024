#include <stdio.h>
#include <limits.h>

typedef long long ll;


// Vector ( ax )       ( bx )       ( px )
//        ( ay ) * A + ( by ) * B = ( py )


//    ( ax bx )       ( A )     ( px )
//    ( ay by )  *    ( B )   = ( py )

ll cheapest(int ax, int ay, int bx, int by, ll px, ll py)
{

	ll price = LLONG_MAX;

	ll a_presses = 1;
	while (1) {
		ll x = ax * a_presses;
		ll y = ay * a_presses;

		if (x > px) {
			break;
		}

		// Calculate number of b presses required
		if ((px - x) % bx == 0) {
			ll b_presses = (px - x) / bx;

			y += b_presses * by;

			if (y == py) {
				ll new_price = a_presses * 3 + b_presses;
				price = new_price < price ? new_price : price;
			}
		}
		a_presses++;
	}

	return price == LLONG_MAX ? -1 : price;
}

int main()
{
	int ax, ay, bx, by;
	ll px, py;

	ll part1 = 0;
	ll part2 = 0;
	ll price;

	while (1) {
		int s = scanf("Button A: X+%d, Y+%d\n", &ax, &ay);
		if (s == EOF) {
			break;
		}
		scanf("Button B: X+%d, Y+%d\n", &bx, &by);
		scanf("Prize: X=%lld, Y=%lld\n", &px, &py);
		scanf("\n");


		price = cheapest(ax, ay, bx, by, px, py);
		printf("%d %d %d %d : %lld %lld ---> %lld\n", ax, ay, bx, by, px, py, price);

		if (price > 0) {
			part1 += price;
		}

		// px += 10000000000000;
		// py += 10000000000000;

		// price = cheapest(ax, ay, bx, by, px, py);
		// printf("%d %d %d %d : %lld %lld ---> %lld\n", ax, ay, bx, by, px, py, price);

		// if (price > 0) {
		// 	part2 += price;
		// }
	}

	printf("Part 1: %lld\n", part1);
	printf("Part 2: %lld\n", part2);

	return 0;
}
