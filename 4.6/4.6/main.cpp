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

std::vector<int> min_coins(std::vector<int> coins, const int V);

std::vector<int> read(std::ifstream& input, std::ofstream& output);

void write(std::map<int, int>& out, std::ofstream& output);

void write(std::string && out, std::ofstream& output);

int main()
{
	std::ifstream input(INPUT_PATH);
	std::ofstream output(OUTPUT_PATH);
    try
    {
        auto result = read(input, output);
		if (result.empty())
		{
			output << "No" << std::endl;
			return 0;
		}
        for (auto coin : result)
        {
            if (coin <= 0)
            {
                output << "No" << std::endl;
                return 0;
            }
        }

        std::map<int, int> out;

        for (auto coin : result)
        {
            ++out[coin];
        }

        write(out, output);
    }
    catch (std::exception& ex)
    {
		write("No", output);
        std::cerr << ex.what() << std::endl;
    }
}

std::vector<int> min_coins(std::vector<int> coins, const int V)
{
    std::vector<int> table(V + 1, 0);
    std::vector<int> result(V + 1, 0);
    std::vector<int> output;

    table[0] = 0;

    for (auto i = 1; i <= V; i++)
    {
        table[i] = INT_MAX;
        result[i] = -1;
    }

    for (auto i = 1; i <= V; i++)
    {
        for (std::size_t j = 0; j < coins.size(); j++)
        {
            if (coins[j] <= i)
            {
                auto sub_res = table[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < table[i])
                {
                    table[i] = sub_res + 1;
                    result[i] = j;
                }
            }
        }
    }
	if (result[V] == -1)
	{
		return output;
	}
    auto start = V;
    while (start != 0)
    {
        const auto j = result[start];
        output.push_back(coins[j]);
        start = start - coins[j];
    }

    return output;
}

std::vector<int> read(std::ifstream& input, std::ofstream& output)
{
    if (!input.is_open())
    {
        throw std::runtime_error("Cannot open file" + INPUT_PATH);
    }

    auto max_money = 0;
    auto number_of_coins = 0;

    input >> max_money;
    if (max_money < ONE || max_money > MAX_MONEY)
    {
        throw std::runtime_error("The amount of money exceeded");
    }

    input >> number_of_coins;
    if (number_of_coins < ONE || number_of_coins > MAX_NUMBER_OF_COIN_TYPE)
    {
        throw std::runtime_error("Number of coin types exceeded");
    }

    std::vector<int> v(number_of_coins);
    for (auto i = 0; i < number_of_coins; i++)
    {
        input >> v[i];
        if (v[i] < ONE || v[i] > MAX_COST_OF_COIN_TYPE)
        {
            throw std::runtime_error("Cost of coin type exceeded");
        }
    }

    std::sort(v.begin(), v.end());

    if (number_of_coins != v.size())
    {
        throw std::runtime_error("The number of coin types does not match");
    }

    auto result = min_coins(v, max_money);

    std::sort(result.rbegin(), result.rend());
    return result;
}

void write(std::map<int, int>& out, std::ofstream& output)
{
    output << out.size() << " ";
    auto quantity = 0;

    for (auto&& value : out)
    {
        quantity += value.second;
    }

    output << quantity << std::endl;

    auto depth = 0;

    std::vector<int> keys;
    keys.reserve(out.size());

    for (auto&& pair : out)
    {
        keys.push_back(pair.first);
    }

    std::reverse(keys.begin(), keys.end());

    for (auto key : keys)
    {
        output << key << " " << out.at(key) << std::endl;
        depth++;
    }
}

void write(std::string && out, std::ofstream & output)
{
	output << out.data() << std::endl;
}
