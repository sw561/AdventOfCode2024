#include <cstdio>
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <array>
#include <map>

using namespace std;

/*
 * +---+---+---+
 * | 7 | 8 | 9 |
 * +---+---+---+
 * | 4 | 5 | 6 |
 * +---+---+---+
 * | 1 | 2 | 3 |
 * +---+---+---+
 *     | 0 | A |
 *     +---+---+
 *
 *
 *     +---+---+
 *     | ^ | A |
 * +---+---+---+
 * | < | v | > |
 * +---+---+---+
 *
 *
 */

typedef array<int, 2> Point;

map<char, Point> numeric_keypad {
	{'7', Point{0, 0}},
	{'8', Point{0, 1}},
	{'9', Point{0, 2}},
	{'4', Point{1, 0}},
	{'5', Point{1, 1}},
	{'6', Point{1, 2}},
	{'1', Point{2, 0}},
	{'2', Point{2, 1}},
	{'3', Point{2, 2}},
	{'0', Point{3, 1}},
	{'A', Point{3, 2}},
	};

map<char, Point> directional_keypad {
	{'^', Point{0, 1}},
	{'A', Point{0, 2}},
	{'<', Point{1, 0}},
	{'v', Point{1, 1}},
	{'>', Point{1, 2}},
	};


void navigate_to(vector<char>& path, const map<char, Point> &keypad, Point& pos, char destination)
{
	Point d = keypad.at(destination);

	while (pos[1] < d[1]) {
		path.push_back('>');
		pos[1]++;
	}
	while (pos[1] > d[1]) {
		path.push_back('<');
		pos[1]--;
	}
	while (pos[0] < d[0]) {
		path.push_back('v');
		pos[0]++;
	}
	while (pos[0] > d[0]) {
		path.push_back('^');
		pos[0]--;
	}
}


int main()
{
	string s;

	while(getline(cin, s)) {
		vector<char> path;

		Point pos = numeric_keypad.at('A');
		for (const char& c : s) {
			navigate_to(path, numeric_keypad, pos, c);
			path.push_back('A');
		}

		// for (const char& c : path) {
		// 	cout << c;
		// }
		// cout << endl;

		vector<char> path2;
		pos = directional_keypad.at('A');
		for (const char& c : path) {
			navigate_to(path2, directional_keypad, pos, c);
			path2.push_back('A');
		}

		// for (const char& c : path2) {
		// 	cout << c;
		// }
		// cout << endl;

		vector<char> path3;
		pos = directional_keypad.at('A');
		for (const char& c : path2) {
			navigate_to(path3, directional_keypad, pos, c);
			path3.push_back('A');
		}

		// for (const char& c : path3) {
		// 	cout << c;
		// }
		// cout << endl;

		cout << s << " " << path3.size() << endl;


		// break;
	}

	return 0;
}
