#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

// В функцию передаётся количество аргументов (которые обычно пердаются
// через коммандную строку) и сслыка на массив символов
// Нулевым элементом обычно идёт название программы
int main(int argc, char* argv[])
{
	int i;

	cout << "I am created" << endl;

	cout << "My name is : ";

	// Передаём название *.exe
	cout << argv[0] << endl;

	for (i = 1; i < argc; ++i)
		cout << "\n My " << i << " parameter = " << argv[i] << endl;

	cout << "Press any key to finish." << endl;

	system("pause");

	return 0;
}

