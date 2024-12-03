#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>

bool comp(int a, int b) {
	return a >= b;
}

int main() {

	std::vector<int> v1 = {
		3, 4, 2, 1, 3, 3
	};

	std::vector<int> v2 = {
		4, 3, 5, 3, 9, 3
	};

	sort(v1.begin(), v1.end(), comp);
	sort(v2.begin(), v2.end(), comp);

	int distance = 0;

	for (std::size_t i{0}; i < v1.size(); i++) {
		if (v1[i] > v2[i]) {
			distance += v1[i] - v2[i];
		} else {
			distance += v2[i] - v1[i];
		}
	}

	std::cout << distance << '\n';

	return 0;
}
