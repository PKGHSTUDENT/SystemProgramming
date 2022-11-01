#include <windows.h>
#include <iostream>
using namespace std;


int main()
{
	char c;
	HANDLE hStdOut;
	DWORD dwLength;
	DWORD dwWritten;
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		cout << "Get standard handle failed." << endl;
		return GetLastError();
	}

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		cout << "Console screen buffer info failed." << endl;
		return GetLastError();
	}

	dwLength = csbi.dwSize.X * csbi.dwSize.Y;
	
	coord.X = 0;
	coord.Y = 0;
	
	cout << "Input any char to fill screen buffer: ";
	cin >> c;
	
	if (!FillConsoleOutputCharacter(
		hStdOut,
		c,
		dwLength,
		coord,
		&dwWritten))
	{
		cout << "Fill console output character failed." << endl;
		return GetLastError();
	}

	cout << "In order to clear screen buffer, press any char: ";
	cin >> c;

	if (!FillConsoleOutputCharacter(
		hStdOut,
		' ',
		dwLength,
		coord,
		&dwWritten))
	{
		cout << "Fill console output character failed." << endl;
		return GetLastError();
	}

	return 0;
}