/*
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

void filling_vector_months(std::string months[])
{
	months[0] = "JANUARY";  months[1] = "FEBRUARY";  months[2] = "MARCH";  months[3] = "APRIL";
	months[4] = "MAY";  months[5] = "JUNE";  months[6] = "JULY";  months[7] = "AUGUST";
	months[8] = "SEPTEMBER";  months[9] = "OCTOBER";  months[10] = "NOVEMBER"; months[11] = "DECEMBER";
}

auto filling_array_days_in_month(int month_days[])
{
	month_days[0] = 31;  month_days[1] = 28;  month_days[2] = 31;  month_days[3] = 30;
	month_days[4] = 31;  month_days[5] = 30;  month_days[6] = 31;  month_days[7] = 31;
	month_days[8] = 30;  month_days[9] = 31;  month_days[10] = 30; month_days[11] = 31;
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	int month_days[12];
	std::string months[12];

	filling_vector_months(months);
	filling_array_days_in_month(month_days);

	int first_year;
	int second_year;
	input >> first_year >> second_year;

	auto week_day = 2;
	auto leap_year = 1;

	for (auto year = start_year; year <= second_year; year++)
	{
		for (auto month = 1; month <= months_in_year; month++)
		{
			for (auto day = 1; day <= month_days[month - 1]; ++day)
			{
				if ((week_day == 5) && (day == 13) && (year >= first_year))
					output << year << " " << months[month - 1].data() << std::endl;
				if (week_day == 7)
					week_day = 1;
				else
					week_day++;
				if ((leap_year == 4) && (month == 2) && (day == 28))
				{
					if (week_day == 7)
						week_day = 1;
					else
						week_day++;
				}
			}
		}
		if (leap_year == 4)
			leap_year = 1;
		else
			++leap_year;
	}
}