#include <windows.h>
#include <iostream>
using namespace std;


int main()
{
	char c;
	HANDLE hStdOut;
	COORD coord;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "Input new cursor position." << endl;
	cout << "X = ";
	cin >> coord.X;
	cout << "Y = ";

	cin >> coord.Y;

	if (!SetConsoleCursorPosition(hStdOut, coord))
	{
		cout << "Set cursor position failed." << endl;
		return GetLastError();
	}

	cout << "This is a new position." << endl;

	system("pause");
	return 0;
}