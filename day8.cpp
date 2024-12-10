#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <numeric>

using namespace std;

typedef array<int,2> Point;

bool valid(Point x, int N) {
	return x[0] >= 0 && x[0] < N && x[1] >= 0 && x[1] < N;
}

Point add_points(Point x, Point y) {
	return {x[0] + y[0], x[1] + y[1]};
}

Point sub_points(Point x, Point y) {
	return {x[0] - y[0], x[1] - y[1]};
}
void add_to_set(vector<vector<bool>>& anodes, Point p, int * count)
{
	// Add 1 if false
	*count += anodes[p[0]][p[1]] ? 0 : 1;
	anodes[p[0]][p[1]] = true;
}

int main()
{
	string s;
	int N=0;
	vector<vector<Point>> locations(75);

	while (getline(cin, s)) {
		for (int j = 0; j < (int)s.size(); j++) {
			if (s[j] != '.') {
				int index = (int)s[j] - (int)'0';
				locations[index].push_back({{N, j}});
			}
		}
		++N;
	}

	vector<vector<bool>> anodes_part1(N, vector<bool>(N, false));
	int count_part1=0;
	vector<vector<bool>> anodes_part2(N, vector<bool>(N, false));
	int count_part2=0;

	for (auto v : locations) {
		for (size_t i=0; i < v.size(); i++) {
			for (size_t j=0; j < v.size(); j++) {
				if (i==j) continue;

				// Part 1
				Point c = sub_points(add_points(v[j], v[j]), v[i]);

				if (valid(c, N)) {
					add_to_set(anodes_part1, c, &count_part1);
				}

				// Part2
				if (i > j) continue;
				c = sub_points(v[j], v[i]);
				int g = gcd(c[0], c[1]);
				// printf("c=(%d,%d) g=%d\n", c[0],c[1],g);
				c[0] /= g;
				c[1] /= g;

				// printf("(%d,%d) (%d,%d) (%d,%d)\n",
				// 	v[i][0], v[i][1], v[j][0], v[j][1], c[0], c[1]);

				array<int, 2> p = v[i];
				while (valid(p, N)) {
					add_to_set(anodes_part2, p, &count_part2);
					p = add_points(p, c);
				}
				p = v[i];
				while (valid(p, N)) {
					add_to_set(anodes_part2, p, &count_part2);
					p = sub_points(p, c);
				}
			}
		}
	}

	// for (int i=0; i<N; i++) {
	// 	for (int j=0; j<N; j++) {
	// 		printf("%c", anodes_part2[i][j] ? '#' : '.');
	// 	}
	// 	printf("\n");
	// }

	printf("Part 1: %d\n", count_part1);
	printf("Part 2: %d\n", count_part2);

	return 0;
}
