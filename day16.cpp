#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <queue>

using namespace std;

typedef array<int,2> Point;

Point add_points(Point x, Point y) {
	return {x[0] + y[0], x[1] + y[1]};
}

// Point direction(char d) {
// 	switch (d) {
// 		case '>':
// 			return Point{0, 1};
// 		case '^':
// 			return Point{-1, 0};
// 		case 'v':
// 			return Point{ 1, 0};
// 		case '<':
// 			return Point{0, -1};
// 		default:
// 			assert(false && "Unreachable");
// 	}
// }


void show_map(vector<string>& m) {
	for (const string& x: m) {
		printf("%s\n", x.c_str());
	}
}

int main()
{
	vector<string> m;
	string s;

	Point start{0};
	Point end{0};

	while (getline(cin, s)) {
		for (int j=0; j < (int)s.size(); j++) {
			if (s[j] == 'S') {
				start = Point{(int)m.size(), j};
			} else if (s[j] == 'E') {
				end = Point{(int)m.size(), j};
			}
		}
		m.push_back(s);
	}

	show_map(m);
	printf("Start: (%d,%d) ", start[0], start[1]);
	printf("End  : (%d,%d)\n", end[0], end[1]);
}
