/*
11.8. Пересечение отрезков (5)
Два отрезка на плоскости заданы целочисленными координатами своих концов в декартовой
системе координат. Требуется определить, существует ли у них общая точка.
Ввод из файла INPUT.TXT. В первой строке содержатся координаты первого конца первого
отрезка, во второй - второго конца первого отрезка, в третьей и четвёртой - координаты концов
второго отрезка.
Вывод в файл OUTPUT.TXT. Выводится Yes, если общая точка есть, или No - в противном
случае.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <fstream>

struct Point
{
	int x;
	int y;
};

void comparison(const Point point1, const Point point2, int & y1)
{
	if (point1.y < point2.y)
	{
		y1 = point2.y;
	}
	else
	{
		y1 = point1.y;
	}
}

int position(const Point point1, const Point point2, const Point point3)
{
	return ((point3.x - point1.x) * (point2.y - point1.y) - (point3.y - point1.y) * (point2.x - point1.x));
}


int check_pos(const int point_position)
{
	if (point_position < 0)
	{
		return -1;
	}
	else
	{
		return (point_position == 0) ? 0 : 1;
	}
}

bool check(const Point point1, const Point point2, const Point point3, const Point point4)
{
	if ((point2.x < point3.x) || 
		(point1.x > point4.x))
	{
		return false;
	}

	int y1, y2;
	comparison(point1, point2, y1);
	comparison(point3, point4, y2);

	if (((y1 < point3.y) && (y1 < point4.y)) || 
		((y2 < point1.y) && (y1 < point2.y)))
	{
		return false;
	}

	const auto p1 = check_pos(position(point1, point2, point3));
	const auto p2 = check_pos(position(point1, point2, point4));
	const auto p3 = check_pos(position(point3, point4, point1));
	const auto p4 = check_pos(position(point3, point4, point2));

	return ((p1 * p2 <= 0) && (p3 * p4 <= 0));
}

void swap(Point & point1, Point & point2)
{
	if (point1.x > point2.x)
	{
		const auto temp = point1;
		point1 = point2;
		point2 = temp;
	}
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	Point point1;
	Point point2;
	Point point3;
	Point point4;

	input >> point1.x >> point1.y;
	input >> point2.x >> point2.y;
	input >> point3.x >> point3.y;
	input >> point4.x >> point4.y;

	swap(point1, point2);
	swap(point3, point4);

	if (check(point1, point2, point3, point4))
	{
		output << "Yes";
	}
	else
	{
		output << "No";
	}
}