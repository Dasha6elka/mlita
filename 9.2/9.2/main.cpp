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
	int num;
	input >> num;

	const long long counter = num - num / 2 - num / 3 + num / 6 - num / 5 + num / 10 + num / 15 - num / 30;

	output << counter;
}