/*
4.6. Размен денег (6)
Требуется разменять заданную сумму денег минимальным количеством монет.
Ввод. Первая строка файла INPUT.TXT содержит сумму денег L (1 ≤ L ≤ 1500) и количество
типов монет N (1 ≤ N ≤ 20). Вторая строка содержит N значений C i через пробел: стоимости типов
монет (1 ≤ C i ≤ 1000).
Вывод. В первой строке выводится количество типов монет K, необходимое для размена, и
общее минимальное количество монет M. В следующих K строках выводятся через пробел по 2
числа: стоимость монеты и количество экземпляров данной монеты. Эти K строк должны
выводится в порядке убывания стоимости монет. Если имеется несколько вариантов решения,
достаточно вывести любой из них. Если указанную сумму разменять невозможно, то выходной
файл должен содержать No.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

const std::string INPUT_PATH = "input.txt";
const std::string OUTPUT_PATH = "output.txt";
const int ONE = 1;
const int MAX_MONEY = 1500;
const int MAX_NUMBER_OF_COIN_TYPE = 20;
const int MAX_COST_OF_COIN_TYPE = 1000;

std::vector<int> minNumberOfCoins(std::vector<int> &values, int number);

std::vector<int> read(std::ifstream &input, std::ofstream &output);

void write(std::map<int, int> &out, std::ofstream &output);

int main()
{
	try
	{
		std::ifstream input(INPUT_PATH);
		std::ofstream output(OUTPUT_PATH);

		std::vector<int> result = read(input, output);
		for (auto result1 : result)
		{
			if (result1 <= 0)
			{
				output << "No" << std::endl;
				return 0;
			}
		}

		std::map<int, int> out;

		for (int val : result)
		{
			++out[val];
		}

		write(out, output);
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

std::vector<int> minNumberOfCoins(std::vector<int> &values, int number) {
	std::vector<int> costs;
	costs.push_back(0);
	std::vector<int> coins_used;

	for (int i = 1; i <= number; i++) {
		int bestCost = INT_MAX;
		int bestCoin = -1;
		for (std::vector<int>::iterator coin = values.begin(); coin != values.end(); ++coin) {
			if (*coin <= i) {
				int cost = 1 + costs[i - *coin];
				if (cost < bestCost) {
					bestCost = cost;
					bestCoin = *coin;
				}
			}
		}
		costs.push_back(bestCost);
		coins_used.push_back(bestCoin);
	}
	std::vector<int> ret;
	while (number > 0) {
		ret.push_back(coins_used[number - 1]);
		number -= coins_used[number - 1];
	}
	return ret;
}

std::vector<int> read(std::ifstream &input, std::ofstream &output)
{
	if (!input.is_open())
	{
		throw std::runtime_error("Cannot open file" + INPUT_PATH);
	}

	int l = 0;
	int n = 0;

	input >> l;
	if (l < ONE || l > MAX_MONEY)
	{
		throw std::runtime_error("The amount of money exceeded");
	}
	input >> n;
	if (n < ONE || n > MAX_NUMBER_OF_COIN_TYPE)
	{
		throw std::runtime_error("Number of coin types exceeded");
	}
	std::vector<int> v(n);
	for (int i = 0; i < n; i++)
	{
		input >> v[i];
		if (v[i] < ONE || v[i] > MAX_COST_OF_COIN_TYPE)
		{
			throw std::runtime_error("Cost of coin type exceeded");
		}
	}
	std::sort(v.begin(), v.end());

	int size = v.size();
	if (n != size)
	{
		throw std::runtime_error("The number of coin types does not match");
	}

	std::vector<int> result = minNumberOfCoins(v, l);

	std::sort(result.rbegin(), result.rend());
	return result;
}

void write(std::map<int, int> &out, std::ofstream &output)
{
	output << out.size() << " ";
	int quantity = 0;

	for (auto &&value : out)
	{
		quantity += value.second;
	}
	output << quantity << std::endl;
	int depth = 0;
	std::vector<int> keys;
	for (auto &&pair : out)
	{
		keys.push_back(pair.first);
	}
	std::reverse(keys.begin(), keys.end());
	for (int key : keys)
	{
		std::string spaces(depth, ' ');
		output << spaces.data() << key << " " << out.at(key) << std::endl;
		depth++;
	}
}
