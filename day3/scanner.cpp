#include <iostream>
#include <fstream>
#include <regex>

std::vector<std::string> getFileInput(std::ifstream &f) {
	std::vector<std::string> matches;

	std::string line;
	std::regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");

	while (std::getline(f, line)) {
		std::sregex_iterator currentMatch(line.begin(), line.end(), pattern);
		std::sregex_iterator lastMatch;


		while (currentMatch != lastMatch) {
			matches.push_back(currentMatch->str());
			currentMatch++;
		}
	}

	return matches;
}

int atoi(char c) {
	return c - '0';
}

int handleInput(std::string m) {

	// Extract the integers
	int val1 {0};
	int val2 {0};

	int end {};
	for (int i = 4; m[i] != ','; i++) {
		val1 *= 10;
		val1 += atoi(m[i]);
		end = i;
	}



	for (int i = end + 2; m[i] != ')'; i++) { // end + 1 to skip over ','
		val2 *= 10;
		val2 += atoi(m[i]);
	}


	return val1 * val2;
}

int main(int argc, char *argv[]) {

	// Get input from file
	std::ifstream f(argv[1]);
	std::vector<std::string> matches = getFileInput(f);
	f.close();


	int sum {0};

	for (auto s : matches) {
		sum += handleInput(s);
	}

	std::cout << "Final sum: " << sum << '\n';

	return 0;
}
