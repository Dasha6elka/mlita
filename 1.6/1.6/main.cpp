/*
1.6. Домино (7)
Имеется N костей игры домино. На каждой кости имеется два числа (каждое от 0 до 6). Требуется написать программу,
которая будет определять максимальное число, составленное из цифр на костях цепочки, составленной по правилам домино из имеющихся костей.
Ввод. Первая строка входного файла содержит целое число N – количество костей (2  N  20).
Следующие N строк содержат два целых числа X и Y (0  X, Y  6), разделенные пробелом.
Вывод. В выходной файл необходимо вывести максимальное целое число, цифры которого соответствуют значению костей в цепочке.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

const int MAX_COUNT = 20;
const int MIN_COUNT = 2;
const int MAX_DOMINO_VALUE = 7;
const std::string INPUT_PATH= "input.txt";
const std::string OUTPUT_PATH= "output.txt";

void read(std::vector<std::vector<int>>& frequency);

void find_max_number(std::string& current, std::string& max_number, std::vector<std::vector<int>> frequency);

void write(std::string max_number);

int main()
{
	try
	{
		std::vector<std::vector<int>> frequency;
		std::string current;
		std::string max_number;

		read(frequency);

		find_max_number(current, max_number, frequency);

		write(max_number);
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

void read(std::vector<std::vector<int>>& frequency)
{
	std::ifstream input(INPUT_PATH);
	if (!input.is_open())
	{
		throw std::runtime_error("Cannot open file" + INPUT_PATH);
	}
	frequency.resize(MAX_DOMINO_VALUE);
	for (int i = 0; i < MAX_DOMINO_VALUE; ++i)
	{
		for (int j = 0; j < MAX_DOMINO_VALUE; ++j)
		{
			frequency[i].push_back(0);
		}
	}
	std::string line;
	std::getline(input, line);
	auto count = std::stoi(line);

	if (count < MIN_COUNT || count > MAX_COUNT)
	{
		throw std::runtime_error("Bone count does not match");
	}

	while (count > 0)
	{
		if (input.eof())
		{
			break;
		}
		else
		{
			int left, right;
			input >> left >> right;
			if (((left < 0) || (left > 6)) || ((right < 0) || (right > 6)))
			{
				throw std::runtime_error("The bone number exceeds the maximum");
			}
			++frequency[left][right];
			++frequency[right][left];
		}
		--count;
	}

	if (count > 0)
	{
		throw std::runtime_error("Your number of dominos is not equal to the Domino number listed");
	}
}

void find_max_number(std::string& current, std::string& max_number, std::vector<std::vector<int>> frequency)
{
	if (max_number.size() < current.size() || (max_number.size() == current.size() && max_number < current))
	{
		max_number = current;
	}

	if (current.empty())
	{
		for (int i = 0; i < MAX_DOMINO_VALUE; ++i)
		{
			for (int j = 0; j < MAX_DOMINO_VALUE; ++j)
			{
				if (i == 0 && j == 0)
				{
					continue;
				}
				if (frequency[i][j] > 0)
				{
					current.push_back(char(i + '0'));
					current.push_back(char(j + '0'));
					--frequency[i][j];
					--frequency[j][i];
					find_max_number(current, max_number, frequency);
					current.pop_back();
					current.pop_back();
					++frequency[i][j];
					++frequency[j][i];
				}
			}
		}
	} else
	{
		int digit = current.back() - '0';
		for (int j = 0; j < MAX_DOMINO_VALUE; ++j)
		{
			if (frequency[digit][j] > 0)
			{
				current.push_back(char(digit + '0'));
				current.push_back(char(j + '0'));
				--frequency[digit][j];
				--frequency[j][digit];
				find_max_number(current, max_number, frequency);
				current.pop_back();
				current.pop_back();
				++frequency[digit][j];
				++frequency[j][digit];
			}
		}
	}
}

void write(const std::string max_number)
{
	std::ofstream output(OUTPUT_PATH);
	output << max_number;
	std::cout << max_number << std::endl;
}
