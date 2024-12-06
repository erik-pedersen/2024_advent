#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>

static void getInput(std::map<int, std::vector<int>> &m, std::vector<std::vector<int>> &v, char *argv[]);
static int handleInput(std::map<int, std::vector<int>> &m, const std::vector<std::vector<int>> &v);
static bool checkSeen(std::map<int, std::vector<int>> &m, std::vector<int> &row);
static std::pair<int,int> inSeenArray(int update, std::vector<std::pair<int, int>> seenArray);
static void swap(std::vector<int> &v, int x, int y);

int main(int argc, char *argv[]) {

	std::map<int, std::vector<int>> m; // Maps page p to a vector of pages that cannot proceed p
	std::vector<std::vector<int>> v; // vector of updates to be made

	getInput(m, v, argv);
	handleInput(m, v);

	std::cout << "Count: " << handleInput(m,v) << '\n';

	return 0;
}

static void getInput(std::map<int, std::vector<int>> &m, std::vector<std::vector<int>> &v, char *argv[]) {
	std::ifstream rules(argv[1]);
	std::ifstream updates(argv[2]);
	std::string string;
	int before {};
	int page {};
	char delimiter {};

	// Insert into map
	while (std::getline(rules, string)) {
		std::istringstream stream(string);
		stream >> before >> delimiter >> page;
		m[page].push_back(before);
	}

	// Insert into vector
	while (std::getline(updates, string)) {
		std::istringstream stream(string);
		int n {};
		char c {};
		std::vector<int> updateList;

		while (stream >> n) {
			stream >> c; // get rid of '|'
			updateList.push_back(n);
		}

		v.push_back(updateList);
	}
}

static int handleInput(std::map<int, std::vector<int>> &m, const std::vector<std::vector<int>> &v) {

	int count{0};

	for (auto row : v) {
		if (checkSeen(m, row)) {
			while (checkSeen(m, row));
			count += row[row.size() / 2];
		}
	}

	return count;
}

static bool checkSeen(std::map<int, std::vector<int>> &m, std::vector<int> &row) {
	std::vector<std::pair<int, int>> seenArray;
	bool flag {false};
	for (auto update : row) {
		std::pair<int, int> p = inSeenArray(update, seenArray);
		if (p != std::pair(-1, -1)) {
			swap(row, p.second, update);
			flag = true;
		}

		// mark pages that we do not want to see in future
		for (auto page : m[update]) {
			seenArray.push_back(std::pair(page, update));
		}
	}


	return flag;
}

static std::pair<int, int> inSeenArray(int update, std::vector<std::pair<int, int>> seenArray) {
	for (auto p : seenArray) {
		if (update == p.first) return p;
	}

	return std::pair(-1, -1); //garbage std::pair
}

// segfaults if x or y are not present in the vector
static void swap(std::vector<int> &v, int x, int y) {
	std::vector<int>::iterator first;
	std::vector<int>::iterator second;
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		if (*it == x) {
			first = it;
		}

		if (*it == y) {
			second = it;
		}
	}

	std::iter_swap(first, second);
}
