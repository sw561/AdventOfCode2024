#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

// Generate ternary permutations by looping from 0 -> 3**n-1
// And get ith term by getting ith value

typedef long long ll;

int ndigits(ll x) {
	return (int)(log10((float)x)) + 1;
}

int evaluate_all_part1(ll * operands, int N, ll test_value)
{
	int total_permutations = (1 << (N-1));
	for (int perm=0; perm < total_permutations; perm++) {
		ll ret = operands[0];
		for (int i=1, p=perm; i < N; i++, p/=2) {
			switch(p % 2) {
				case 0:
					ret += operands[i];
					break;
				case 1:
					ret *= operands[i];
					break;
				default:
					assert(0), "Unreachable";
			}
		}
		if (ret == test_value) {
			return 1;
		}
	}
	return 0;
}

int evaluate_all_part2(ll * operands, int N, ll test_value)
{
	int p10ndigits_[N] = {};
	for (int i=1; i < N; i++) {
		p10ndigits_[i] = pow(10, ndigits(operands[i]));
	}

	int total_permutations = pow(3, N-1);
	for (int perm=0; perm < total_permutations; perm++) {
		ll ret = operands[0];
		for (int i=1, p=perm; i < N; i++, p/=3) {
			switch(p%3) {
				case 0:
					ret += operands[i];
					break;
				case 1:
					ret *= operands[i];
					break;
				case 2:
					ret = (ret * p10ndigits_[i]) + operands[i];
					break;
				default:
					assert(0), "Unreachable";
			}
			if (ret > test_value) {
				break;
			}
		}
		if (ret == test_value) {
			return 1;
		}
	}
	return 0;
}

int main()
{
	size_t n = 100;
	char * buffer = malloc(n * sizeof(char));

	ll * operands = malloc(n * sizeof(ll));

	ll part1 = 0;
	ll part2 = 0;

	while (getline(&buffer, &n, stdin) > 0) {
		char * buf_ptr = buffer;
		ll value;
		int n;
		sscanf(buf_ptr, "%lld: %n", &value, &n);
		buf_ptr += n;

		int ri = 0;
		char x = '0';
		do {
			sscanf(buf_ptr, "%lld%n", operands+ri, &n);
			ri += 1;
			buf_ptr += n;

			sscanf(buf_ptr, "%c", &x);
			buf_ptr += 1;
		} while (x == ' ');

		if(evaluate_all_part1(operands, ri, value)) {
			part1 += value;
		}
		if(evaluate_all_part2(operands, ri, value)) {
			part2 += value;
		}
	}

	printf("Part 1: %lld\n", part1);
	printf("Part 2: %lld\n", part2);

	free(buffer);
	free(operands);
	return 0;
}

