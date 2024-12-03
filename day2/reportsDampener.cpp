#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool checkRate(std::vector<int> r);
bool checkMonotonic(std::vector<int> r);
bool checkModified(std::vector<int> report, int ignore);
int abs(int x);


int main() {

	// Read that shit in 
	
	std::string input;
	std::vector<std::vector<int>> reports;
	std::ifstream f("big.txt");

	while (getline(f, input)) {
		std::vector<int> newReport;
		std::istringstream iss(input);
		int num;

		while (iss >> num) {
			newReport.push_back(num);
		}

		reports.push_back(newReport);
	}

	f.close();

//	for (auto r : reports) {
//		std::cout << "New Report: " << '\n';
//		for (auto l : r) {
//			std::cout << l << '\n';
//		}
//	}

	// Sort that shit out
	int safety {0};

	for (auto r : reports) {
		if (checkMonotonic(r) && checkRate(r)) {
			std::cout << "Safe!\n";
			safety++;
			continue;
		} 

		if (!checkMonotonic(r)) {
			std::cout << "Not monotonic! ";
		}

		if (!checkRate(r)) {
			std::cout << "Not good rate!";
		}

		// Check if deleting a single element helps
		for (int ignore = 0; ignore < r.size(); ignore++) {
			if (checkModified(r, ignore)) {
				safety++;
				std::cout << "Saved by deleting " << r[ignore] << " (" << ignore << ")";
				break;
			}
		}

		std::cout << '\n';
	}

	std::cout << "Safety: " << safety << '\n';
	return 0;
}

bool checkModified(std::vector<int> report, int ignore) {
	// Create r, which is same as 'report' but without 'ignore' index
	std::vector<int> r;

	for (int i = 0; i < report.size(); i++) {
		if (i == ignore) continue;
		r.push_back(report[i]);
	}

	// Now perform checks as before
	return checkMonotonic(r) && checkRate(r);
}


bool checkMonotonic(std::vector<int> r) {
	if (r[1] > r[0]) { // Increasing
		for (int i = 1; i < r.size(); i++) {
			if (r[i] <= r[i-1]) {
				return false;
			}
		}

	} else if (r[0] > r[1]) { // Decreasing
		for (int i = 1; i < r.size(); i++) {
			if (r[i] >= r[i-1]) {
				return false;
			}
		}
	}

	return true;
}

bool checkRate(std::vector<int> r) {
	for (int i = 1; i < r.size(); i++) {
		if ((abs(r[i] - r[i-1]) < 1) || abs(r[i] - r[i-1]) > 3) 
			return false;
	}

	return true;
}

int abs(int x) {
	if (x < 0) return -x;

	return x;
}
