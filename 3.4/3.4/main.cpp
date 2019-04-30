/*
3.4. K-ичные числа (4)
Найти количество натуральных N-значных (1 ≤ N ≤ 20) чисел в системе счисления с
основанием K (2 ≤ K ≤ 8), таких, что их запись не содержит двух подряд идущих нулей.
Ввод из файла INPUT.TXT. В единственной строке содержатся числа N и K в десятичной
записи, разделенные пробелом.
Вывод в файл OUTPUT.TXT. Программа должна выдать искомое число в десятичной записи.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <vector>
#include "fstream"

std::ifstream input("input.txt");
std::ofstream output("output.txt");

int main() {
	long long num1, num2;
	input >> num1 >> num2;

	std::vector<long long> arr(30);
	arr[0] = 1;
	arr[1] = num2 - 1;

	auto i = 2;
	while (i <= num1) {
		arr[i] = (arr[i - 1] + arr[i - 2]) * (num2 - 1);
		++i;
	}

	output << arr[num1];
}