#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cassert>

using namespace std;

typedef array<int,2> Point;

Point add_points(Point x, Point y) {
	return {x[0] + y[0], x[1] + y[1]};
}

Point direction(char d) {
	switch (d) {
		case '>':
			return Point{0, 1};
		case '^':
			return Point{-1, 0};
		case 'v':
			return Point{ 1, 0};
		case '<':
			return Point{0, -1};
		default:
			assert(false && "Unreachable");
	}
}


bool move(vector<string>& m, const Point& d, Point& robot_pos)
{
	Point new_pos = add_points(robot_pos, d);

	switch (m[new_pos[0]][new_pos[1]]) {
		case '#':
			return false;
		case 'O':
			Point n(new_pos);
			if (!move(m, d, n)) {
				return false;
			}
	}

	m[new_pos[0]][new_pos[1]] = m[robot_pos[0]][robot_pos[1]];
	m[robot_pos[0]][robot_pos[1]] = '.';

	robot_pos = new_pos;
	return true;
}

void show_map(vector<string>& m) {
	for (const string& x: m) {
		printf("%s\n", x.c_str());
	}
}


int gps(const vector<string>& m) {
	int score = 0;
	for (int i=0; i < (int)m.size(); i++) {
		for (int j=0; j < (int)m[i].size(); j++) {
			if (m[i][j] == 'O') {
				score += 100 * i + j;
			}
		}
	}

	return score;
}


int main()
{
	vector<string> m;
	string s;

	string instructions = "";

	bool reading_map = true;

	Point robot_pos{0};

	while (getline(cin, s)) {
		if (s == "") {
			reading_map = false;
			continue;
		}
		if (reading_map) {
			for (int j=0; j < (int)s.size(); j++) {
				if (s[j] == '@') {
					robot_pos = Point{(int)m.size(), j};
				}
			}
			m.push_back(s);
		} else {
			instructions.append(s);
		}
	}

	for (const char& d : instructions) {
		move(m, direction(d), robot_pos);
	}
	// show_map(m);

	int part1 = gps(m);
	printf("Part 1: %d\n", part1);

	return 0;
}
