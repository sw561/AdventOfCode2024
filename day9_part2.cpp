#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

typedef struct Block {
	int pos, size, ID;
} Block;

void print(deque<Block> d)
{
	for (auto b : d) {
		printf("(%d,%d,%d) ", b.pos, b.size, b.ID);
	}
	printf("\n");
}

void print_mem(deque<Block> occupied, deque<Block> spaces)
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

long long checksum(deque<Block> occupied)
{
	long long ret = 0;
	for (auto b : occupied) {
		for (int pos = b.pos; pos < b.pos + b.size; pos++) {
			ret += pos * b.ID;
		}
	}
	return ret;
}

int main()
{
	string s;
	getline(cin, s);

	deque<Block> spaces;
	deque<Block> occupied;

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
			if (x > 0) {
				spaces.push_back(Block{
					.pos=pos,
					.size=x,
					.ID=-1});
			}
		}
		pos += x;
	}

	// print(occupied);
	// print(spaces);
	// print_mem(occupied,spaces);

	// deque<Block> new_occupied;

	for (auto oit = occupied.rbegin(); oit != occupied.rend(); oit++) {
		auto sit = spaces.begin();
		bool found_move = false;
		for (; sit != spaces.end(); sit++) {
			if (sit->pos > oit->pos) break;
			if (sit->size >= oit->size) {
				found_move = true;
				break;
			}
		}

		if (!found_move) continue;

		oit->pos = sit->pos;

		if (sit->size > oit->size) {
			sit->pos  += oit->size;
			sit->size -= oit->size;
		} else {
			spaces.erase(sit);
		}

		// print_mem(occupied,spaces);
	}

	// print(occupied);
	// print(spaces);
	// print_mem(occupied,spaces);

	printf("Part 2: %lld\n", checksum(occupied));

	return 0;
}


