#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

static void getInput(std::map<int, std::vector<int>> &m, std::vector<std::vector<int>> &v, char *argv[]);

int main(int argc, char *argv[]) {

	std::map<int, std::vector<int>> m; // Maps page p to a vector of pages that cannot proceed p
	std::vector<std::vector<int>> v; // vector of updates to be made

	getInput(m, v, argv);

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
			stream >> c;
			updateList.push_back(n);
		}

		v.push_back(updateList);
	}
}
