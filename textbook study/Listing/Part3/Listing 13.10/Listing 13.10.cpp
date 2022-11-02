#include <windows.h>
#include <iostream>
using namespace std;



int main()
{
	HANDLE hStdOut;
	CHAR_INFO ci[80 * 25];
	COORD size;
	COORD coord;
	SMALL_RECT sr;
	
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int i = 0; i < 80 * 25; ++i)
	{
		ci[i].Char.AsciiChar = ' ';
		ci[i].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	}
	
	coord.X = 0;
	coord.Y = 0;
	size.X = 80;
	size.Y = 25;
	
	cout << "Input left coordinate to write: ";
	cin >> sr.Left;
	cout << "Input top coordinate to write: ";
	cin >> sr.Top;
	cout << "Input right coordinate to write: ";
	cin >> sr.Right;
	cout << "Input down coordinate to write: ";
	cin >> sr.Bottom;
	
	if (!WriteConsoleOutput(
		hStdOut,
		ci,
		size,
		coord,
		&sr))
	{
		cout << "Write console output failed." << endl;
		return GetLastError();
	}

	system("pause");

	return 0;
}