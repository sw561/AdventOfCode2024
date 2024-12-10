#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template<typename T>
void onelinevector(T v)
{
	for (int i=0; i < (int)v.size(); i++) {
		if (v[i] >= 0) {
			printf("%d ", v[i]);
		} else {
			printf(". ");
		}
	}
	printf("\n");
}

int main()
{
	vector<int> mem;

	string s;
	getline(cin, s);

	deque<int> spaces;
	deque<int> occupied;

	int ID=0;

	for (int i=0; i<(int)s.size(); i++) {
		int x = (int)(s[i]) - (int)'0';

		for (int j=0; j < x; j++) {
			occupied.push_back(mem.size());
			mem.push_back(ID);
		}

		i++;

		x = (int)(s[i]) - (int)'0';

		for (int j=0; j < x; j++) {
			spaces.push_back(mem.size());
			mem.push_back(-1);
		}

		ID++;
	}

	// onelinevector(mem);
	// onelinevector(spaces);
	// onelinevector(occupied);
	// printf("------------\n");

	while (!occupied.empty() && !spaces.empty()) {
		int src  = occupied.back();
		int dest = spaces.front();

		if (src <= dest) break;

		occupied.pop_back();
		spaces.pop_front();

		int val = mem[src];
		mem[src] = -1;
		mem[dest] = val;
	}

	// onelinevector(mem);
	// onelinevector(spaces);
	// onelinevector(occupied);

	long long checksum = 0;
	for (int i=0; i < (int)mem.size(); i++) {
		if (mem[i] < 0) break;
		checksum += i * mem[i];
	}

	printf("Part 1: %lld\n", checksum);

	return 0;
}

