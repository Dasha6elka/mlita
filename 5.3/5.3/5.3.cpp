/*
5.3. Число цифр (5)
Найти суммарное число цифр во всех целых числах от M до N включительно.
Ввод из файла INPUT.TXT. В единственной строке находятся целые числа M и N (1 ≤ M ≤
N ≤ 10 15 ).
Вывод в файл OUTPUT.TXT. В единственную строку вывести суммарное число цифр.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <cmath>
#include "fstream"
#include <string>

std::fstream input("input.txt");
std::ofstream output("output.txt");

long number_of_tens(const long length_num);

int main() {
	long num1, num2;
	input >> num1 >> num2;
	auto s_num1 = std::to_string(num1);
	auto s_num2 = std::to_string(num2);

	const auto count_num = num2 - num1 + 1;
	long result = 0;

	if (s_num2.length() == s_num1.length()) {
		result = count_num * s_num2.length();
	}
	else {
		long length_num2 = s_num2.length();
		while (length_num2 >= s_num1.length())
		{
			long count = length_num2 - 1;
			long number = num2 - number_of_tens(count) + 1;
			num2 = number_of_tens(count) - 1;
			if (length_num2 == s_num1.length()) {
				number = number - num1 + number_of_tens(count);
			}
			result += number * length_num2;
			length_num2--;
		}
	}

	output << result;
}

long number_of_tens(const long length_num) {
	long num_of_tens = 1;
	for (auto i = 0; i < length_num; i++) {
		num_of_tens *= 10;
	}
	return num_of_tens;
}