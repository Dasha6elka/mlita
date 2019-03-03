// 4.6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

std::vector<int> minNumberOfCoins(std::vector<int>& values, int number) {
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

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	int l = 0;
	int n = 0;
	std::vector<int> coinsUsed;
	std::vector<int> coinCount;

	input >> l;
	input >> n;
	std::vector<int> v(n);
	for (int i = 0; i < n; i++)
	{
		input >> v[i];
	}
	std::sort(v.begin(), v.end());

	std::vector<int> result = minNumberOfCoins(v, l);

	std::sort(result.rbegin(), result.rend());
	std::map<int, int> out;

	auto i = 0;
	int count = 1;

	for (int val: result)
	{
		++out[val];
	}
	
	int size = out.size();
	output << size << " ";
	int quantity = 0;

	for (auto &&value : out)
	{
		quantity += value.second;
	}
	output << quantity << std::endl;
	auto space = " ";
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
