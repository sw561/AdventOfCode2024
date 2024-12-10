#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void onelinevector(vector<int> v)
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

	vector<int> spaces;
	vector<int> occupied;

	int ID=0;

	int pos=0;
	for (int i=0; i<(int)s.size(); i++) {
		int x = (int)(s[i]) - (int)'0';

		if (i%2==0) {
			for (int j=0; j < x; j++) {
				occupied.push_back(pos++);
				mem.push_back(ID);
			}
			ID++;
		} else {
			for (int j=0; j < x; j++) {
				spaces.push_back(pos++);
				mem.push_back(-1);
			}
		}
	}

	// onelinevector(mem);
	// onelinevector(spaces);
	// onelinevector(occupied);
	// printf("------------\n");

	auto oit=occupied.rbegin();
	auto sit=spaces.begin();
	for ( ;oit != occupied.rend() && sit != spaces.end(); oit++, sit++) {
		int src  = *oit;
		int dest = *sit;

		if (src <= dest) break;

		// occupied.pop_back();
		// spaces.pop_front();

		mem[dest] = mem[src];
		mem[src] = -1;
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
