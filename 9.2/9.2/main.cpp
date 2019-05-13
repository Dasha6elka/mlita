/*
9.2. Простоватые числа (4)
Студент Вася отыскивает простые числа в диапазоне от 1 до N (1 ≤  N ≤ 10 15 ). Если число M, не
превосходящее N, не делится на 2, 3 и 5, Вася называет его “простоватым”. По заданному
значению N найти количество простоватых чисел.
Ввод. В единственной строке файла INPUT.TXT находится число N.
Вывод. В единственную строку файла OUTPUT.TXT вывести количество простоватых чисел.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <fstream>

std::ifstream input("input.txt");
std::ofstream output("output.txt");

int main()
{
	long long counter = 0;
	long long num;

	input >> num;

	if (num >= 60) {
		const long long number = num % 60;
		counter = (num / 60) * 16 + number;
	} else {
		for (auto i = 1; i <= num; i += 2) {
			if ((i % 3 != 0) && (i % 5 != 0)) {
				counter++;
			}
		}
	}
	output << counter;
}