#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int MAX_LENGTH = 100;
const int BASE = 10;

struct BigInt
{
	int amount;
	std::vector<int> digits;

	BigInt();

	explicit BigInt(std::string const& value);

	void level_up();

	void print();
};

BigInt::BigInt()
{
	amount = 0;
	digits = std::vector<int>(MAX_LENGTH, 0);
}

BigInt::BigInt(std::string const& value)
{
	digits = std::vector<int>(MAX_LENGTH, 0);
	amount = value.size();
	std::vector<char> data(value.begin(), value.end());
	std::reverse(data.begin(), data.end());
	for (std::size_t i = 0; i < data.size(); ++i)
	{
		digits[i] = data[i] - 48;
	}
}

void BigInt::level_up()
{
	for (auto i = amount; i >= 1; i--)
	{
		digits[i] = digits[i - 1];
	}
	if (digits[amount])
	{
		amount++;
	}
}

void BigInt::print()
{
	for (auto i = amount - 1; i >= 0; i--)
	{
		std::cout << digits[i];
	}
}

bool operator ==(const BigInt& left, const BigInt& right)
{
	if (left.amount != right.amount)
	{
		return false;
	}
	for (auto i = 0; i < left.amount; i++)
	{
		if (left.digits[i] != right.digits[i])
		{
			return false;
		}
	}
	return true;
}

bool operator >(const BigInt& left, const BigInt& right)
{
	if (left.amount != right.amount)
	{
		return left.amount > right.amount;
	}
	for (auto i = left.amount - 1; i >= 0; i--)
	{
		if (left.digits[i] != right.digits[i])
		{
			return left.digits[i] > right.digits[i];
		}
	}
	return false;
}

bool operator <(const BigInt& left, const BigInt& right)
{
	if (left.amount != right.amount)
	{
		return left.amount < right.amount;
	}
	for (auto i = left.amount - 1; i >= 0; i--)
	{
		if (left.digits[i] != right.digits[i])
		{
			return left.digits[i] < right.digits[i];
		}
	}
	return false;
}

BigInt operator *(const BigInt& left, const int& right)
{
	BigInt result;
	result.amount = left.amount;

	auto radix = 0;
	for (auto i = 0; i < result.amount | radix; i++)
	{
		result.digits[i] = left.digits[i] * right + radix;
		radix = result.digits[i] / BASE;
		result.digits[i] -= radix * BASE;
	}
	if (result.digits[result.amount])
	{
		result.amount++;
	}

	return result;
}

BigInt operator -(const BigInt& left, const BigInt& right)
{
	BigInt result = left;

	for (auto i = 0; i < result.amount; i++)
	{
		result.digits[i] -= right.digits[i];
		if (result.digits[i] < 0)
		{
			result.digits[i] += BASE;
			result.digits[i + 1]--;
		}
	}

	auto pos = result.amount;
	while (pos && !result.digits[pos])
	{
		pos--;
	}
	result.amount = pos + 1;
	return result;
}

BigInt operator %(const BigInt& left, const BigInt& right)
{
	BigInt result;
	BigInt current_value;
	for (auto i = left.amount - 1; i >= 0; i--)
	{
		current_value.level_up();
		current_value.digits[0] = left.digits[i];
		auto x = 0;
		auto l = 0;
		auto radix = BASE;
		while (l <= radix)
		{
			auto m = (l + radix) >> 1;
			auto current = right * m;
			if (current < current_value || current == current_value)
			{
				x = m;
				l = m + 1;
			}
			else
			{
				radix = m - 1;
			}
		}
		result.digits[i] = x;
		current_value = current_value - right * x;
	}
	return current_value;
}

BigInt operator /(const BigInt& left, const BigInt& right)
{
	BigInt result;
	BigInt current_value;
	for (auto i = left.amount - 1; i >= 0; i--)
	{
		current_value.level_up();
		current_value.digits[0] = left.digits[i];
		auto x = 0;
		auto l = 0;
		auto radix = BASE;
		while (l <= radix)
		{
			auto m = (l + radix) >> 1;
			auto current = right * m;
			if (current < current_value || current == current_value)
			{
				x = m;
				l = m + 1;
			}
			else
			{
				radix = m - 1;
			}
		}
		result.digits[i] = x;
		current_value = current_value - right * x;
	}
	auto pos = left.amount;
	while (pos >= 0 && !result.digits[pos])
	{
		pos--;
	}
	result.amount = pos + 1;
	return result;
}

std::istream& operator>>(std::istream& in, BigInt& number)
{
	auto i = 0;
	auto size = number.amount;
	std::vector<int> buffer(size, 0);
	while (size-- > 0)
	{
		char ch = 0;
		in >> ch;
		buffer[i] = ch - 48;
		i++;
	}
	std::reverse(buffer.begin(), buffer.end());
	for (auto i = 0; i < number.amount; ++i)
	{
		number.digits[i] = buffer[i];
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, BigInt& number)
{

	for (auto i = number.amount - 1; i >= 0; i--)
	{
		out << number.digits[i];
	}
	return out;
}

int main()
{
	try
	{
		BigInt left;
		BigInt right;

		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		input >> left.amount >> right.amount;
		input >> left >> right;

		auto div = left / right;
		auto mod = left % right;
		output << div << std::endl << mod <<  std::endl;
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}
