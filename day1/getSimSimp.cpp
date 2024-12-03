#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>

int main() {

	std::vector v1 = {3, 4, 2, 1, 3, 3};
	std::vector v2 = {4, 3, 5, 3, 9, 3};

	std::map<int, int> map;

	for (auto n : v2) {
		map[n] = 0;
	}

	for (auto n : v2) {
		map[n]++;
	}

	// print out the map
	for (auto n : v2) {
		std::cout << map[n] << '\n';
	}

	int score = 0;

	for (auto m : v1) {
		score += m * map[m];
	}

	std::cout << score << '\n';

	return 0;
}
