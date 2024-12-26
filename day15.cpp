#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>
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

bool check_move(vector<string>& m, const Point& d, const set<Point>& to_move)
{
	// To check if we can make a move, check if we can move all of the next
	// blocks that will be required

	if (to_move.size() == 0) {
		return true;
	}

	set<Point> to_move_next;

	// printf("To move: ");
	for (const Point& p : to_move) {
		// printf("(%d,%d) ", p[0], p[1]);
		Point n = add_points(p, d);

		if (m[n[0]][n[1]] == '#') {
			// printf("\n");
			return false;
		}

		if (m[n[0]][n[1]] == '.') {
			continue;
		}

		if (d[0] != 0) { // Vertical move
			if (m[n[0]][n[1]] == ']') {
				to_move_next.insert(n);
				to_move_next.insert(Point{n[0], n[1]-1});
			} else if (m[n[0]][n[1]] == '[') {
				to_move_next.insert(n);
				to_move_next.insert(Point{n[0], n[1]+1});
			} else if (m[n[0]][n[1]] == 'O') {
				to_move_next.insert(n);
			}
		} else {
			to_move_next.insert(n);
		}
	}
	// printf("\n");

	if (!check_move(m, d, to_move_next)) {
		return false;
	}

	for (const Point& p : to_move) {
		Point n = add_points(p, d);

		m[n[0]][n[1]] = m[p[0]][p[1]];
		m[p[0]][p[1]] = '.';
	}

	return true;
}

Point move_robot(vector<string>& m, const Point& d, const Point& robot_pos)
{
	set<Point> to_move;
	to_move.insert(robot_pos);

	if (check_move(m, d, to_move)) {
		return add_points(robot_pos, d);
	}
	return robot_pos;
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
			if (m[i][j] == 'O' || m[i][j] == '[') {
				score += 100 * i + j;
			}
		}
	}

	return score;
}

int count_boxes(const vector<string>& m) {
	int count = 0;
	for (int i=0; i < (int)m.size(); i++) {
		for (int j=0; j < (int)m[i].size(); j++) {
			if (m[i][j] == 'O' || m[i][j] == '[') {
				count++;
			}
		}
	}

	return count;
}

int main()
{
	vector<string> m;
	vector<string> m2;
	string s;

	string instructions = "";

	bool reading_map = true;

	Point robot_pos{0};
	Point robot_pos_part2{0};

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
			string part2 = "";
			for (int j=0; j < (int)s.size(); j++) {
				switch (s[j]) {
					case '#':
						part2.append("##");
						break;
					case 'O':
						part2.append("[]");
						break;
					case '.':
						part2.append("..");
						break;
					case '@':
						part2.append("@.");
						robot_pos_part2 = Point{(int)m2.size(), 2*j};
						break;
					default:
						assert(false && "Unreachable");
				}
			}
			m2.push_back(part2);
		} else {
			instructions.append(s);
		}
	}

	const int count = count_boxes(m);
	assert(count == count_boxes(m2));

	for (const char& d : instructions) {
		// printf("Robot pos: (%d,%d)  ", robot_pos_part2[0], robot_pos_part2[1]);
		// printf("Move: %c Count: %d\n", d, count);

		robot_pos = move_robot(m, direction(d), robot_pos);
		robot_pos_part2 = move_robot(m2, direction(d), robot_pos_part2);

		if (m2[robot_pos_part2[0]][robot_pos_part2[1]] != '@') {
			printf("Found a problem\n");
			break;
		}

		if (count_boxes(m2) != count) {
			printf("COUNT PROBLEM\n");
			assert(false);
		}
	}
	show_map(m2);

	int part1 = gps(m);
	int part2 = gps(m2);
	printf("Part 1: %d\n", part1);
	printf("Part 2: %d\n", part2);

	return 0;
}
