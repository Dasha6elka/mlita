/*
15.2. Игра в умножение (5)
Двое играют в умножение: умножают целое число P на одно из чисел от 2 до 5. Первый игрок
всегда начинает с P=1, делает умножение, затем число умножает второй игрок, снова первый и т.
д. Перед началом игры им задают число N, и победителем считается тот, кто первым добьется
условия P ≥ N. Определить, кто выиграет при заданном N, если оба играют наилучшим образом.
Ограничения: 2  N 10000, время 1 с.
Ввод из файла INPUT.TXT. В первой строке находится количество партий M. В следующих M
строках задаются значения N для каждой партии.
Вывод в файл OUTPUT.TXT. Выводится М строк с числами 1 – если победит первый игрок,
или 2 - если победит второй.
Щеглова Дарья ПС-23
Microsoft Visual C++ 2017
Версия 15.9.6
 */

#include "pch.h"
#include "fstream"
#include "string"

std::ifstream input("input.txt");
std::ofstream output("output.txt");

void main() 
{
	float count_part = 0;
	input >> count_part;

	while (count_part)
	{
		float m = 0;
		float n = 0;
		input >> n;

		float N = n;
		bool isFirst = true;
		while (n > 1)
		{
			if (isFirst)
			{
				m = n = N = N / 5;
				isFirst = false;
			}
			else
			{
				m = n = N = m / 2;
				isFirst = true;
			}
		}

		if (!isFirst)
		{
			output << 1 << std::endl;
		} else
		{
			output << 2 << std::endl;
		}

		count_part--;
	}
}