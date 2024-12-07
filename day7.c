#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

// Generate ternary permutations by looping from 0 -> 3**n-1
// And get ith term by getting ith value

typedef long long int ll;

int ith_bool(int perm, int i) {
	return (perm & (1 << i)) > 0;
}

int ith_tern(int perm, int i) {
	return (perm / (int)pow(3, i)) % 3;
}

int ndigits(ll x) {
	return (int)(log10((double)x) + 1);
}

ll evaluate(ll * operands, size_t N, int perm)
{
	ll ret = operands[0];
	for (int i=1; i < (int)N; i++) {
		switch(ith_bool(perm, i-1)) {
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
	return ret;
}

int evaluate_all(ll * operands, size_t N, ll test_value)
{
	for (int perm=0; perm < (1 << (N-1)); perm++) {
		if (evaluate(operands, N, perm) == test_value) {
			return 1;
		}
	}
	return 0;
}

ll evaluate_part2(ll * operands, size_t N, int perm)
{
	ll ret = operands[0];
	for (int i=1; i < (int)N; i++) {
		switch(ith_tern(perm, i-1)) {
			case 0:
				ret += operands[i];
				break;
			case 1:
				ret *= operands[i];
				break;
			case 2:
				ret = (ret * pow(10, ndigits(operands[i]))) + operands[i];
				break;
			default:
				assert(0), "Unreachable";
		}
	}
	return ret;
}

int evaluate_all_part2(ll * operands, size_t N, ll test_value)
{
	for (int perm=0; perm < pow(3, N-1); perm++) {
		if (evaluate_part2(operands, N, perm) == test_value) {
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

		size_t ri = 0;
		char x = '0';
		do {
			sscanf(buf_ptr, "%lld%n", operands+ri, &n);
			ri += 1;
			buf_ptr += n;

			sscanf(buf_ptr, "%c", &x);
			buf_ptr += 1;
		} while (x == ' ');

		// printf("%lld: ", value);
		// for (size_t i=0; i < ri; i++) {
		// 	printf("%lld ", operands[i]);
		// }
		int e1 = evaluate_all(operands, ri, value);
		int e = evaluate_all_part2(operands, ri, value);
		// printf("EVAL: %d", e);
		// printf("\n");

		if (e1) {
			part1 += value;
		}

		if (e) {
			part2 += value;
		}
	}

	printf("Part 1: %lld\n", part1);
	printf("Part 2: %lld\n", part2);

	free(buffer);
	free(operands);
	return 0;
}

