#include "pch.h"
#include <vector>
#include "fstream"

std::ifstream input("input.txt");
std::ofstream output("output.txt");

int main() {
	long num1, num2;
	input >> num1 >> num2;

	std::vector<long> arr(200);
	arr[0] = 1;
	arr[1] = num2 - 1;

	auto i = 2;
	while (i <= num1) {
		arr[i] = (arr[i - 1] + arr[i - 2]) * (num2 - 1);
		++i;
	}

	output << arr[num1];
}