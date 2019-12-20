#include <iostream>
#include <string>
#include <Windows.h>
#include <math.h>
#include <conio.h>

using namespace std;

int circled(int start, int way, int& k)
{
	int a = start + way;
	int res = k - 1;

	if (a > res) return 0;
	if (a < 0) return res;
}

void next(int** array, int start, int now, int all, int& k, int& wayQuant)
{

	if (now == 1)
	{
		array[wayQuant][all - now] = circled(start, +1, k);

		for (int i = 0; i < all - now; i++) array[wayQuant + 1][i] = array[wayQuant][i];
		wayQuant++;

		array[wayQuant][all - now] = circled(start, -1, k);

		for (int i = 0; i < all - now; i++) array[wayQuant + 1][i] = array[wayQuant][i];
		wayQuant++;
	}
	else
	{
		array[wayQuant][all - now] = circled(start, +1, k);
		next(array ,circled(start, +1, k), now - 1, all, k, wayQuant);
		array[wayQuant][all - now] = circled(start, -1, k);
		next(array, circled(start, -1, k), now - 1, all, k, wayQuant);
	}
}

void countWays(int** array, int n, int& x, int& y, int& z, int& k, int& wayQuant)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | 15));


	int goodway = 0;
	int stone_bomb = 0;

	next(array, x, n, n, k, wayQuant);

	cout << endl << endl;

	for (int i = 0; i < pow(2, n); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | 15));

		if (array[i][n - 1] == y)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((10 << 4) | 0));
			goodway++;
		}

		for (int j = 0; j < n * n; j++) if (array[i][j] == z && (array[i][n - 1] == y))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((4 << 4) | 0));
			stone_bomb++;
			break;
		}

		cout << x;
		for (int j = 0; j < n; j++) cout << " -> " + to_string(array[i][j]);
		cout << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | 15));
	cout << endl;
	cout << "Количество возможных путей = " << pow(2, n) << endl;
	cout << "Количество путей в Y = " << goodway << endl;
	cout << "Количество путей в которых есть камень = " << stone_bomb << endl;
	cout << "Количество путей в которых нет камня = " << goodway - stone_bomb << endl;
	cout << "Вероятность попадания на мину = " << (goodway - stone_bomb) / pow(2, n);

	cout << endl << endl;
}

int main()
{
	setlocale(0, "");

	int N, x = 0, y = 0, z = 0, k = 0, wayQuant = 0, Rows = 1048576, Cols = 20;

	do {

		int** array = new int* [Rows];
		for (int i = 0; i < Rows; i++)
		{
			array[i] = new int[Cols];
		}

		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				array[i][j] = 0;
			}
		}

		do {
			cout << "Укажите параметры задачи:" << endl;
			cout << "Количество прыжков от 2 до 18: ";
			cin >> N;

			if ((N > 1 && N <= 18))
			{
				
				cout << "Начальная вершина: "; cin >> x;
				cout << "Конечная вершина: "; cin >> y;
				cout << "Вершина c камнем (миной): "; cin >> z;
				cout << "Количество углов многоугольника: "; cin >> k;

				countWays(array, N, x, y, z, k, wayQuant);

			}
			else cout << "Ошибка ввода. Пожалуйста, вводите целое число в естесственном виде арабскими цифрами." << endl;

			cin.clear(); // Очистка флага и сдвиг буфера
			cin.ignore(cin.rdbuf()->in_avail());
		} while (!(N > 1 && N <= 18));


		for (int i = 0; i < Rows; i++)
		{
			delete[] array[i];
		}
		delete[] array;

		cout << "Продолжить? Esc для выхода";
		auto code = _getch();
		if (code == 27) break;
		else cout << endl << endl << endl << "=============================================" << endl << endl << endl;

	} while (true);
}