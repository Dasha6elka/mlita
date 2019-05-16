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

const float min_num = 2;
const float max_num = 5;

void search_win(float n, bool & is_first)
{
	auto first = n;
	float second = 0;
	while (n > 1)
	{
		if (is_first)
		{
			second = first / max_num;
			n = first / max_num;
			first /= max_num;

			is_first = false;
		} else
		{
			first = second / min_num;
			n = second / min_num;
			second /= min_num;

			is_first = true;
		}
	}
}

void main() 
{
	float count_part = 0;
	input >> count_part;

	while (count_part > 0)
	{
		float n = 0;
		input >> n;
		auto is_first = true;

		search_win(n, is_first);

		if (!is_first)
		{
			output << 1 << std::endl;
		} else
		{
			output << 2 << std::endl;
		}

		count_part--;
	}
}