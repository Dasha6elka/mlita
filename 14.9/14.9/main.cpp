﻿/*
14.9.Пятница 13 (5)
Перечислить дни, на которые приходится пятница 13 - го числа в заданном диапазоне лет из
интервала 1901 - 2099 г.г.
Ввод из файла INPUT.TXT.В единственной строке задаются через пробел начальный и
конечный годы.
Вывод в файл OUTPUT.TXT.Выводится столько строк, сколько найдено пятниц 13 - го числа.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
*/

#include "pch.h"
#include <fstream>

const int months_in_year = 12;
const int start_year = 1901;
const int end_year = 2099;
std::ifstream input("input.txt");
std::ofstream output("output.txt");

void search_friday_13(int first_year, int second_year, std::string months[], const int days_in_months[]);

int main()
{
	 std::string months[12] = {
		"JANUARY", "FEBRUARY", "MARCH", 
		"APRIL", "MAY", "JUNE", 
		"JULY", "AUGUST", "SEPTEMBER", 
		"OCTOBER", "NOVEMBER","DECEMBER"
	};
	int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	int first_year;
	int second_year;
	input >> first_year >> second_year;

	search_friday_13(first_year, second_year, months, days_in_months);
}

void friday_13(const int week_day, const int day, const int year, const int first_year, std::string months[], const int month)
{
	if ((week_day == 5) && (day == 13) && (year >= first_year))
	{
		output << year << " " << months[month - 1].data() << std::endl;
	}
}

void fun_leap_year(const int month, const int day, const int leap_year, int & week_day)
{
	if ((leap_year == 4) && (month == 2) && (day == 28))
	{
		if (week_day == 7)
		{
			week_day = 1;
		}
		else
		{
			week_day++;
		}
	}
}

void search_friday_13(const int first_year, const int second_year, std::string months[], const int days_in_months[])
{
	auto week_day = 2;
	auto leap_year = 1;

	for (auto year = start_year; year <= second_year; year++)
	{
		for (auto month = 1; month <= months_in_year; month++)
		{
			for (auto day = 1; day <= days_in_months[month - 1]; ++day)
			{
				friday_13(week_day, day, year, first_year, months, month);
				if (week_day == 7)
				{
					week_day = 1;
				}
				else
				{
					week_day++;
				}
				fun_leap_year(month, day, leap_year, week_day);
			}
		}
		if (leap_year == 4)
		{
			leap_year = 1;
		}
		else
		{
			++leap_year;
		}
	}
}