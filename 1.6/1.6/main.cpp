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
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <algorithm>

std::vector<std::string> read_file(const std::string &path){
	std::vector<std::string> result{};
	std::string line;
	std::ifstream input;
	input.open(path);
	if (!input.is_open())
	{
		throw std::runtime_error("Cannot open file" + path);
	}
	std::getline(input, line);
	while (std::getline(input, line))
	{
		result.push_back(line);
		line.clear();
	}
	return result;
}

void search(const int root, std::map<int, std::vector<int>> dict, std::vector<int> number, int size, const int depth, std::vector<int> &results)
{
	// Добавление вершины в число
	number.push_back(root);
	// Если вектор словаря пустой, то конец рекурсии.
	// Переводим вектор цифр числа в строку и в int. Добавляем в вектор результатов.
	if (dict[root].empty())
	{
		std::string string;
		for (auto j : number)
		{
			string += std::to_string(j);
		}
		const auto result = std::stoi(string);
		results.push_back(result);

		return;
	}
	// Если глубина больше 0, добавляем вторую половину кости
	if (depth > 0)
	{
		number.push_back(root);
	}
	// Перебор по вектору ключа из словаря
	for (auto i = 0; i < size; i++)
	{
		auto child = dict[root][i];
		// Удаляем ребёнка из исходного вектора ключа
		dict[root].erase(std::remove(dict[root].begin(), dict[root].end(), child), dict[root].end());
		// Удаляем исходный ключ из вектора ключа ребёнка
		dict[child].erase(std::remove(dict[child].begin(), dict[child].end(), root), dict[child].end());
		// Уменьшаем счётчики т.к. удалили элементы
		size--;
		i--;
		// Рекурсивный поиск
		search(child, dict, number, dict[child].size(), depth + 1, results);
	}

	// Переводим вектор цифр числа в строку и в int. Добавляем в вектор результатов.
	std::string string;
	for (auto j : number)
	{
		string += std::to_string(j);
	}
	const auto result = std::stoi(string);
	results.push_back(result);
}

int main(int argc, char *argv[])
{
	auto max = INT_MIN;
	std::map<int, std::vector<int>> dict;
	auto text = read_file("input.txt");

	// Инициализация списка смежности
	for (auto &bone : text)
	{
		auto first = bone[0] - '0';
		auto second = bone[2] - '0';

		dict[first].push_back(second);
		dict[second].push_back(first);
	}

	// Перебор по списку смежности и поиск
	for (auto &pair : dict)
	{
		std::vector<int> results;
		search(pair.first, dict, std::vector<int>(), dict[pair.first].size(), 0, results);

		// Нахождение максимального из списка результатов
		for (auto && result : results)
		{
			if (result > max)
			{
				max = result;
			}
		}
	}

	std::cout << max << std::endl;
}	
