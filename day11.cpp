#include <cstdio>
#include <iostream>
#include <cmath>
#include <map>

using namespace std;

typedef long long ll;

int ndigits(ll x) {
	return (int)(log10((float)x)) + 1;
}

ll nstones(map<pair<ll,int>,ll> &cache, ll value, int blinks) {
	if (blinks == 0) {
		return 1;
	}

	if (auto search=cache.find(make_pair(value, blinks)); search!=cache.end()) {
		return search->second;
	}

	ll ret = 0;

	if (value == 0) {
		 ret = nstones(cache, 1, blinks-1);
	} else {

		int n = ndigits(value);

		if (n % 2) {
			ret = nstones(cache, value * 2024, blinks-1);
		} else {
			ll d = pow(10, n/2);

			ll a = value / d;
			ll b = value % d;

			// printf("Splitting %lld to (%lld,%lld)\n", value, a, b);

			ret = nstones(cache, a, blinks-1) +
				nstones(cache, b, blinks-1);
		}
	}

	cache[make_pair(value, blinks)] = ret;
	return ret;
}


int main()
{
	// Store number of stones from (initial value, n blinks)
	map<pair<ll,int>,ll> count;

	int d;
	ll part1 = 0;
	ll part2 = 0;
	while (cin >> d) {
		part1 += nstones(count, d, 25);
		part2 += nstones(count, d, 75);;
	}

	printf("Part 1: %lld\n", part1);
	printf("Part 2: %lld\n", part2);

	return 0;
}
