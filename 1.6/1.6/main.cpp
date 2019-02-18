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
#include <algorithm>

struct domino
{
	int left = 0;
	int right = 0;
	bool used = false;
};

const int WRONG_DIGIT = -1;
const int MAX_COUNT = 20;
const int ZERO_CODE = 48;
const int MAX_DOMINO_VALUE = 6;

std::vector<domino> read(const std::string& path);

void write(const std::string& result, const std::string& path);

bool less(const std::string& left, const std::string& right);

std::string find_max_number(std::vector<domino>& dominos, int last_digit);

int main()
{
	try
	{
		auto dominos = read("input.txt");
		const auto max = find_max_number(dominos, WRONG_DIGIT);
		write(max, "output.txt");
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

std::vector<domino> read(const std::string& path)
{
	std::ifstream input(path);
	if (!input.is_open())
	{
		throw std::runtime_error("Cannot open file" + path);
	}
	std::vector<std::string> result{};
	std::string line;
	std::getline(input, line);
	const auto count = std::stoi(line);

	auto i = 0;

	while (std::getline(input, line))
	{
		result.push_back(line);
		line.clear();
		i++;
	}

	if (i != count)
	{
		throw std::runtime_error("The number of bones doesn't match the set number");
	}
	if (count == 0 || count == 1 || count > MAX_COUNT)
	{
		throw std::runtime_error("Bone count does not match");
	}

	std::vector<domino> dominos(count);
	std::size_t j = 0;
	for (auto& d : dominos)
	{
		auto current = result[j];
		d.left = current[0] - ZERO_CODE;
		d.right = current[2] - ZERO_CODE;

		if (d.left > MAX_DOMINO_VALUE || d.right > MAX_DOMINO_VALUE)
		{
			throw std::runtime_error("The bone number exceeds the maximum");
		}

		j++;
	}
	return dominos;
}

void write(const std::string& result, const std::string& path)
{
	std::ofstream output(path);
	output << result;
}

bool less(const std::string& left, const std::string& right)
{
	auto left_copy(left);
	auto right_copy(right);
	const auto left_size = left_copy.size();
	const auto right_size = right_copy.size();
	auto max_size = left_size;
	if (max_size < right_size)
	{
		max_size = right_size;
	}
	left_copy.erase(0, std::min(left_copy.find_first_not_of('0'), left_copy.size() - 1));
	right_copy.erase(0, std::min(right_copy.find_first_not_of('0'), right_copy.size() - 1));
	const auto result = static_cast<int>(left_copy.size() - right_copy.size());
	if (result > 0)
	{
		if (max_size == left_size)
		{
			return false;
		}
	}
	if (result < 0)
	{
		if (max_size == right_size)
		{
			return true;
		}
	}
	for (std::size_t i = 0; i < left_copy.size(); i++)
	{
		if (left_copy[i] > right_copy[i]) return false;
		if (left_copy[i] < right_copy[i]) return true;
	}
	if (max_size == left_size)
	{
		return false;
	}
	if (max_size == right_size)
	{
		return true;
	}
	return left_copy < right_copy;
}

std::string find_max_number(std::vector<domino>& dominos, const int last_digit)
{
	std::string result;

	for (auto& d : dominos)
	{
		if (d.used)
		{
			continue;
		}

		if (last_digit == WRONG_DIGIT || d.left == last_digit)
		{
			auto tmp = std::to_string(d.left) + std::to_string(d.right);
			d.used = true;
			tmp += find_max_number(dominos, d.right);
			d.used = false;
			if (less(result, tmp))
			{
				result = std::move(tmp);
			}
		}

		if (last_digit == WRONG_DIGIT || d.right == last_digit)
		{
			auto tmp = std::to_string(d.right) + std::to_string(d.left);
			d.used = true;
			tmp += find_max_number(dominos, d.left);
			d.used = false;
			if (less(result, tmp))
			{
				result = std::move(tmp);
			}
		}
	}

	return result;
}
