/*
2.8. Калькулятор (7)
Одна фирма выпускает в продажу странные калькуляторы. Они могут выполнять лишь три
операции:
 ввести число 1;
 удвоить текущее число;
 поменять в текущем числе первую и последнюю цифры.
Калькулятор умеет работать лишь с целыми числами от 1 до L (1 ≤ L ≤ 10 5 ). Незначащие нули в
начале числа отбрасываются. Написать программу, которая проверяет, можно ли на данном
калькуляторе получить число N (1 ≤ N ≤ 10 5 ). Если это возможно, выдать самую короткую
последовательность преобразований.
Ввод. В единственной строке находятся через пробел значения число L и N.
Вывод. В первой строке вывести Yes или No. Если значение N достижимо, во второй строке
выдать количество значений в цепочке преобразований от 1 до N, а в третьей строке через пробел
сами эти значения.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

std::ifstream input("input.txt");
std::ofstream output("output.txt");

int counts(int i)
{
	auto count = (i == 0) ? 1 : 0;
	while (i != 0)
	{
		count++;
		i /= 10;
	}
	return count;
}

int get_opposite(const int i)
{
	if (i < 10)
	{
		return i;
	}
	const auto delimiter = static_cast<int>(pow(10, counts(i) - 1));
	return (((i % 10) * delimiter) +
		((i % delimiter / 10) * 10) +
		(i / delimiter));
}

void push_in_path(
	std::unordered_map<int, int> & digits,
	int value,
	int i,
	const int number,
	std::queue<int> & queue)
{
	if (digits.find(value) == digits.end() && value <= number)
	{
		queue.push(value);
		digits.insert(std::pair<int, int>(value, i));
	}
}

bool is_get_number(
	int & i, 
	const int needed, 
	const int number, 
	std::unordered_map<int, int> & digits)
{
	digits.insert(std::pair<int, int>(1, -1));
	std::queue<int> queue;
	queue.push(1);
	while (!queue.empty())
	{
		i = queue.front();
		queue.pop();
		if (i != needed)
		{
			const auto opposite = get_opposite(i);
			push_in_path(digits, i * 2, i, number, queue);
			push_in_path(digits, opposite, i, number, queue);
		}
		else
		{
			break;
		}
	}
	return i == needed;
}

void if_yes(std::unordered_map<int, int> digits, int i)
{
	output << "Yes" << std::endl;

	std::vector<int> path;
	path.push_back(i);

	while (digits[i] != -1)
	{
		i = digits[i];
		path.push_back(i);
	}
	reverse(path.begin(), path.end());

	output << path.size() << std::endl;

	for (auto i = 0; i < path.size(); ++i)
	{
		output << path[i];
		if (i + 1 != path.size())
		{
			output << " ";
		}
	}
}

int main()
{
	int number, needed;
	input >> number >> needed;

	std::unordered_map<int, int> digits;
	auto i = -1;

	if (is_get_number(i, needed, number, digits))
	{
		if_yes(digits, i);
	}
	else
	{
		output << "No" << std::endl;
	}
}