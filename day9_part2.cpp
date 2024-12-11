#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Block {
	int pos, size, ID;
};

void print(vector<Block> d)
{
	for (auto b : d) {
		printf("(%d,%d,%d) ", b.pos, b.size, b.ID);
	}
	printf("\n");
}

void print_mem(vector<Block> occupied, vector<Block> spaces)
{
	std::vector<char> c_arr(1024, '\'');
	int max_pos = 0;

	for (auto b : occupied) {
		for (int j=b.pos; j < b.pos + b.size; j++) {
			c_arr[j] = (char) ((int)'0' + b.ID);
		}
		max_pos = max(max_pos, b.pos + b.size);
	}

	for (auto s: spaces) {
		for (int j=s.pos; j < s.pos + s.size; j++) {
			c_arr[j] = '.';
		}
	}

	for (int i=0; i < max_pos; i++) {
		printf("%c", c_arr[i]);
	}
	printf("\n");
}

int main()
{
	string s;
	getline(cin, s);

	vector<Block> spaces;
	vector<Block> occupied;

	int ID=0;

	int pos=0;
	for (int i=0; i<(int)s.size(); i++) {
		int x = (int)(s[i]) - (int)'0';

		if (i%2==0) {
			occupied.push_back(Block{
				.pos=pos,
				.size=x,
				.ID=ID++});
		} else {
			spaces.push_back(Block{
				.pos=pos,
				.size=x,
				.ID=-1});
		}
		pos += x;
	}

	// print(occupied);
	// print(spaces);
	// print_mem(occupied,spaces);

	for (auto oit = occupied.rbegin(); oit != occupied.rend(); oit++) {
		for (auto sit = spaces.begin(); sit != spaces.end(); sit++) {
			if (sit->pos > oit->pos) break;
			if (sit->size >= oit->size) {

				oit->pos = sit->pos;

				sit->pos  += oit->size;
				sit->size -= oit->size;
				break;
			}
		}
		// print_mem(occupied,spaces);
	}

	// print(occupied);
	// print(spaces);
	// print_mem(occupied,spaces);

	long long checksum = 0;
	for (auto b : occupied) {
		for (int pos = b.pos; pos < b.pos + b.size; pos++) {
			checksum += pos * b.ID;
		}
	}
	printf("Part 2: %lld\n", checksum);

	return 0;
}
