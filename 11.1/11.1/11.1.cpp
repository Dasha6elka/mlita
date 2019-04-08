/*
11.1. Треугольник и точка (5)
В декартовой системе координат на плоскости заданы координаты вершин треугольника и еще
одной точки. Определить, принадлежит ли эта точка треугольнику.
Ввод из файла INPUT.TXT. В четырех строках находятся пары чисел - координаты точек.
Числа в первых трех строках - это координаты вершин треугольника, в четвертой строке -
координаты тестируемой точки.
Вывод в файл OUTPUT.TXT. Вывести In, если точка находится внутри треугольника, или Out -
если снаружи.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include <fstream>

struct point
{
	long long x1, x2;
};

long long area(point one, point two, point tree)
{
	return abs((two.x2 - one.x2) * (tree.x1 - one.x1) - (two.x1 - one.x1) * (tree.x2 - one.x2));
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	point point1;
	point point2;
	point point3;
	point point4;
	input >> point1.x1 >> point1.x2;
	input >> point2.x1 >> point2.x2;
	input >> point3.x1 >> point3.x2;
	input >> point4.x1 >> point4.x2;

	long long first = area(point1, point2, point3);
	long long second = area(point1, point2, point4);
	long long third = area(point2, point3, point4);
	long long four = area(point3, point1, point4);
	if ((second + third + four - first) <= 0)
	{
		output << "In" << std::endl;
	} else
	{
		output << "Out" << std::endl;
	}
}