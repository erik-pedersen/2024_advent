#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

static void getInput(std::map<int, std::vector<int>> &m, std::vector<std::vector<int>> &v, char *argv[]);
static int handleInput(std::map<int, std::vector<int>> &m, const std::vector<std::vector<int>> &v);
static bool checkSeen(std::map<int, std::vector<int>> &m, std::vector<int> row);

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
		if (checkSeen(m, row)) count += row[row.size() / 2];
	}

	return count;
}

static bool checkSeen(std::map<int, std::vector<int>> &m, std::vector<int> row) {
	std::map<int, bool> seenMap;
	for (auto update : row) {
		if (seenMap[update] == true) {
			return false;
		}

		for (auto page : m[update]) {
			seenMap[page] = true;
		}
	}

	return true;
}
