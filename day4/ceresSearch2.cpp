#include <iostream>
#include <fstream>
#include <vector>

static void getInput(std::vector<std::vector<char>> &v, char *fileName);
static void convertStrToV(std::vector<char> &v, std::string string);
int search(const std::vector<std::vector<char>> &v);
static int checkNeighbors(int r, int c, const std::vector<std::vector<char>> &v);
static bool checkForChar(char character, int r, int vertical, 
		int c, int horizontal, const std::vector<std::vector<char>> &v);

int main(int argc, char *argv[]) {

	std::vector<std::vector<char>> v;
	
	// Get input into v
	getInput(v, argv[1]);

	// Search v for matches
	std::cout << "Count: " << search(v) << '\n';

	return 0;
}

int search(const std::vector<std::vector<char>> &v) {
	int count {0};

	for (int r = 0; r < v.size(); r++) {
		for (int c = 0; c < v[r].size(); c++) {
			if (v[r][c] == 'A') 
				count += checkNeighbors(r, c, v);
		}
	}

	return count;
}

static int checkNeighbors(int r, int c, const std::vector<std::vector<char>> &v) {
	int count {0};

	if ((checkForChar('M', r, -1, c, -1, v) && checkForChar('S', r, 1, c, 1, v) 
		|| checkForChar('S', r, -1, c, -1, v) && checkForChar('M', r, 1, c, 1, v))
			&&
	   (checkForChar('M', r, 1, c, -1, v) && checkForChar('S', r, -1, c, 1, v)
	    	|| checkForChar('S', r, 1, c, -1, v) && checkForChar('M' ,r, -1, c, 1, v)
	    )) {
		count++;
	}

	return count;
}

static bool checkForChar(char character, int r, int vertical, 
		int c, int horizontal, const std::vector<std::vector<char>> &v) {
	// check still in bounds of matrix
	if (r + vertical >= 0 
	&& r + vertical < v.size() 
	&& c + horizontal >= 0 
	&& c + horizontal < v[r + vertical].size()) {
		if (v[r + vertical][c + horizontal] == character) {
			return true;
		}
	}

	return false;
}


static void getInput(std::vector<std::vector<char>> &v, char *fileName) {
	std::ifstream file(fileName);
	std::string string;
	int index {0};

	while (std::getline(file, string)) {
		std::vector<char> line {};
		convertStrToV(line, string);
		v.push_back(line);
		index++;
	}
}

static void convertStrToV(std::vector<char> &v, std::string string) {
	for (auto c : string) {
		v.push_back(c);
	}
}
