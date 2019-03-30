/*
10.12. Последовательность 4 (6)
Имеется последовательность целых чисел x 1 , x 2 , …, x n . Найти количество троек чисел, в каждой
из которых одно из чисел равно сумме двух других.
Ввод из файла INPUT.TXT. В первой строке содержится значение n (3 ≤ n ≤ 5000). Во второй
строке заданы через пробел значения x 1 , x 2 , …, x n (1  x i  10 5 ).
Вывод в файл OUTPUT.TXT. В единственной строке выводится количество указанных троек
чисел (x i , x j , x k ).
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
*/

#include "pch.h"
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>

const std::string input_path = "input1.txt";
const std::string output_path = "output.txt";

void write_numbers_in_vector(std::istream& input, std::vector<int>& numbers);

std::unordered_map<int, int> fill_map(std::vector<int> const& numbers);

unsigned long long count_triplets(std::vector<int> const& numbers, std::unordered_map<int, int> const& numbers_map, size_t count);

int main()
{
    try
    {
        std::ifstream input(input_path);
        std::ofstream output(output_path);
        if (!input.is_open())
        {
            throw std::runtime_error("Cannot open file" + input_path);
        }

        std::vector<int> numbers;
        size_t count;

        input >> count;
        numbers.reserve(count * 4);
        write_numbers_in_vector(input, numbers);

        std::sort(numbers.rbegin(), numbers.rend(), [](const int a, const int b) { return a > b; });
        auto numbers_map = fill_map(numbers);

        auto triplets_amount = count_triplets(numbers, numbers_map, count);
        output << triplets_amount << std::endl;
    }
    catch (std::exception const& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

void write_numbers_in_vector(std::istream& input, std::vector<int>& numbers)
{
    int number;
    while (input >> number)
    {
        numbers.push_back(number);
    }
}

std::unordered_map<int, int> fill_map(std::vector<int> const& numbers)
{
    std::unordered_map<int, int> numbers_map;
    for (auto i : numbers)
    {
        ++numbers_map[i];
    }
    return numbers_map;
}

unsigned long long count_triplets(std::vector<int> const& numbers, std::unordered_map<int, int> const& numbers_map, const size_t count)
{
    unsigned long long triplets_amount = 0;
    const auto max_number = numbers[count - 1];
    for (size_t i = 0; i < count; ++i)
    {
        if ((i != count - 1) && ((numbers[i] + numbers[i + 1])) > max_number)
        {
            break;
        }
        for (auto j = i + 1; j < count; ++j)
        {
            auto two_numbers_sum = numbers[i] + numbers[j];
            if (two_numbers_sum > max_number)
            {
                break;
            }
            auto result = numbers_map.find(two_numbers_sum);
            if (result != numbers_map.end())
            {
                triplets_amount += result->second;
            }
        }
    }
    return triplets_amount;
}
