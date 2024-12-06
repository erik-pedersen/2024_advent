#include <iostream>
#include <vector>
#include <fstream>

enum groundType {
	obstacle,
	guard,
	visited,
	visitedGuard,
	empty
};

enum dirs {
	UP,
	RIGHT,
	DOWN,
	LEFT
};


static void getInput(std::vector<std::vector<groundType>> &map, 
		std::pair<int, int> &guardLocation, char *filename);
static void showMap(const std::vector<std::vector<groundType>> &map);
static int handleInput(std::vector<std::vector<groundType>> &map, std::pair<int, int> &guardLocation);
static bool boundsCheck(std::vector<std::vector<groundType>> &map, std::pair<int, int> &guardLocation, enum dirs &guardDirection);
static void guardMove(std::vector<std::vector<groundType>> &map, std::pair<int, int> &guardLocation, enum dirs &guardDirection, int &nVisited, int &count);

int main(int argc, char *argv[]) {

	std::vector<std::vector<groundType>> map;
	std::pair<int, int> guardLocation;

	getInput(map, guardLocation, argv[1]);
	std::cout << "obstacles: " << handleInput(map, guardLocation) << '\n';


	return 0;
}

static void showMap(const std::vector<std::vector<groundType>> &map) {
	for (int i = 0; i < map[0].size(); i++) {
		std::cout << '_';
	}

	std::cout << '\n';
	for (auto v : map) {
		for (auto c : v) {
			switch (c) {
				case groundType::empty: {
											std::cout << '.';
											break;
										}
				case groundType::visitedGuard:
				case groundType::guard: {
											std::cout << '^';
											break;
										}
				case groundType::obstacle: {
											std::cout << '#';
											break;
										}
				case groundType::visited: {
											std::cout << 'X';
											break;
										}
			}
		}
		std::cout << '\n';
	}

	for (int i = 0; i < map[0].size(); i++) {
		std::cout << '_';
	}
}

static void getInput(std::vector<std::vector<groundType>> &map, std::pair<int, int> &guardLocation, char *filename) {
	std::ifstream f(filename);
	std::string string;

	while (std::getline(f, string)) {
		std::vector<groundType> v;
		for (char c : string) {
			switch (c) {
				case '.': { v.push_back(groundType::empty);
							  break;
						  }

				case '^': {v.push_back(groundType::guard);
							  break;
						  }

				case '#': {v.push_back(groundType::obstacle);
							  break;
						  }

				case 'X': {v.push_back(groundType::visited);
							  break;
						  }
			}
		}

		map.push_back(v);
	}

	for (int r = 0; r < map.size(); r++) {
		for (int c = 0; c < map[r].size(); c++) {
			if (map[r][c] == groundType::guard) {
				guardLocation.first = r;
				guardLocation.second = c;
			}
		}
	}
}

static int handleInput(std::vector<std::vector<groundType>> &map, std::pair<int, int> &guardLocation) {
	enum dirs guardDirection {dirs::UP};

	int nObstacles {0};
	int nVisited {0};

	for (int r = 0; r < map.size(); r++) {
		for (int c = 0; c < map[r].size(); c++) {
			int count {0};
			std::vector<std::vector<groundType>> newMap = map;
			std::pair<int, int> newGuardLocation = guardLocation;
			enum dirs newGuardDirection = guardDirection;
			newMap[r][c] = groundType::obstacle;

			std::cout << "r = " << r << " c = " << c << '\n';

			// VERY INEFFICENT AND BAD WAY OF DOING IT LOL
			while (boundsCheck(newMap, newGuardLocation, newGuardDirection)) {
				guardMove(newMap, newGuardLocation, newGuardDirection, nVisited, count);

				if (count > map.size() * map.size() * map[0].size()) {
					nObstacles++;
					break;
				}
			}
		}
	}

	return nObstacles;
}

static bool boundsCheck(std::vector<std::vector<groundType>> &map, std::pair<int, int> &guardLocation, enum dirs &guardDirection) {

	switch (guardDirection) {
		case dirs::UP: {
			if (guardLocation.first - 1 < 0) return false;
			if (map[guardLocation.first - 1][guardLocation.second] == groundType::obstacle) {
				guardDirection = dirs::RIGHT;
			}
			break;
	   }
		case dirs::RIGHT: {
			if (guardLocation.second + 1 >= map[0].size()) return false;
			if (map[guardLocation.first][guardLocation.second + 1] == groundType::obstacle) {
				guardDirection = dirs::DOWN;
			}
			break;
	  	}
		case dirs::DOWN: {
			if (guardLocation.first + 1 >= map.size()) return false;
			if (map[guardLocation.first + 1][guardLocation.second] == groundType::obstacle) {
				guardDirection = dirs::LEFT;
			}
			break;
		}
		case dirs::LEFT: {
			if (guardLocation.second - 1 < 0) return false;
			if (map[guardLocation.first][guardLocation.second - 1] == groundType::obstacle) {
				guardDirection = dirs::UP;
			}
			break;
		}
	}
	
	return true;
}

static void guardMove(std::vector<std::vector<groundType>> &map, std::pair<int, int> &guardLocation, enum dirs &guardDirection, int &nVisited, int &count) {

	if (map[guardLocation.first][guardLocation.second] == groundType::visitedGuard) {
		count++;
	} else {
		count = 0;
	}

	map[guardLocation.first][guardLocation.second] = groundType::visited;

	switch (guardDirection) {
		case dirs::UP: {
			guardLocation.first -= 1;
			break;
	   }

		case dirs::RIGHT: {
			guardLocation.second += 1;
			break;
	  	}

		case dirs::DOWN: {
			guardLocation.first += 1;
			break;
		}

		case dirs::LEFT: {
			guardLocation.second -= 1;
			break;
		}
	}
	if (map[guardLocation.first][guardLocation.second] == groundType::visited) {
		map[guardLocation.first][guardLocation.second] = groundType::visitedGuard;
	} else {
		map[guardLocation.first][guardLocation.second] = groundType::guard;
	}
}
