#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

typedef array<int,2> Point;

bool valid(vector<string> m, Point p) {
	return 0 <= p[0] && p[0] < (int)m.size() && 0 <= p[1] && p[1] < (int)m[p[0]].size();
}

array<Point, 4> ns = {Point{-1,0}, Point{1,0}, Point{0,-1}, Point{0,1}};

Point add_points(Point x, Point y) {
	return {x[0] + y[0], x[1] + y[1]};
}

vector<Point> dfs(vector<string> m, Point p, char c) {
	vector<Point> ret;

	char next = (char) ((int)c + 1);

	for (auto n : ns) {
		Point q = add_points(p, n);

		if (!valid(m, q) || m[q[0]][q[1]] != next) continue;

		if (next == '9') {
			ret.push_back(q);
		} else {
			for (auto p : dfs(m, q, next)) {
				ret.push_back(p);
			}
		}
	}

	return ret;
}

int count_unique(vector<Point> points, int N) {
	int count = 0;
	vector<vector<bool>> present(N, vector<bool>(N, false));

	for (auto p : points) {
		if (present[p[0]][p[1]]) continue;

		present[p[0]][p[1]]	= true;
		count++;
	}

	return count;
}

int main()
{
	vector<string> m;
	string s;

	while (getline(cin, s)) {
		m.push_back(s);
	}

	int part1 = 0;
	int part2 = 0;
	for (int i=0; i < (int)m.size(); i++) {
		for (int j=0; j < (int)m[i].size(); j++) {

			if (m[i][j]!='0') continue;

			auto ret = dfs(m, Point{i, j}, m[i][j]);

			part1 += count_unique(ret, m.size());
			part2 += ret.size();
		}
	}

	printf("Part 1: %d\n", part1);
	printf("Part 2: %d\n", part2);

	return 0;
}

