#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <unordered_map>

using namespace std;

typedef long long ll;

#define WHITE 0
#define BLUE 1
#define BLACK 2
#define RED 3
#define GREEN 4
#define N_COLOURS 5

int get_index(char c)
{
	// printf("char c: %c\n", c);
	switch (c) {
		case 'w':
			return WHITE;
		case 'u':
			return BLUE;
		case 'b':
			return BLACK;
		case 'r':
			return RED;
		default:
			assert(c == 'g');
			return GREEN;
	}
}

struct Node {
	bool is_leaf = false;
	Node * sub_trees[N_COLOURS] = {nullptr};

	~Node() {
		for (int i=0; i < N_COLOURS; i++) {
			if (sub_trees[i] != nullptr) {
				delete sub_trees[i];
			}
		}
	}
};

Node * construct_tree(vector<string> v)
{
	Node * tree = new(Node);

	for (const string& s : v) {

		Node * node = tree;
		for (const char& c : s) {
			if (node->sub_trees[get_index(c)] == nullptr) {
				node->sub_trees[get_index(c)] = new Node;
			}
			node = node->sub_trees[get_index(c)];
		}
		node->is_leaf = true;
	}

	return tree;
}

void display_tree(Node * tree, int level = 0)
{
	for (const char& c : string("wubrg")) {
		Node * node = tree->sub_trees[get_index(c)];
		if (node == nullptr) continue;

		cout << (node->is_leaf ? "--->" : "    ");

		for (int j=0; j < level; j++) {
			cout << " ";
		}
		cout << c << endl;
		display_tree(node, level+1);
	}
}

ll is_buildable(unordered_map<string, ll> &cache, Node * tree, string to_build)
{
	if (to_build.empty()) return 1;

	if (auto search = cache.find(to_build); search!=cache.end()) {
		return search->second;
	}

	Node * node = tree;
	int i = 0;
	ll count_ways = 0;

	while (i < (int)to_build.size()) {
		node = node->sub_trees[get_index(to_build[i])];
		if (node == nullptr) {
			break;
		}
		if (node->is_leaf) {
			count_ways += is_buildable(cache, tree, to_build.substr(i + 1));
		}
		i++;
	}

	cache[to_build] = count_ways;
	return count_ways;
}

int main()
{
	string s;
	vector<string> v;

	getline(cin, s);

	int start = 0;
	while (true) {
		size_t d = s.find(',', start);
		v.push_back(s.substr(start, d-start));
		if (d == string::npos) {
			break;
		}
		start = d + 2;
	}

	getline(cin, s); // Empty line expected

	Node * tree = construct_tree(v);

	// display_tree(tree);

	int part1 = 0;
	ll part2 = 0;
	unordered_map<string, ll> cache;
	while(getline(cin, s)) {
		ll ways = is_buildable(cache, tree, s);
		if (ways > 0) part1++;
		part2 += ways;
	}

	printf("Part 1: %d\n", part1);
	printf("Part 2: %lld\n", part2);

	delete tree;
	return 0;
}
