#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	char c;

	HANDLE hStdOut;
	WORD wAttribute;
	DWORD dwLength;
	DWORD dwWritten;
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	cout << "In order to fill console attributes, input any char: ";
	cin >> c;

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
	
	wAttribute = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	
	if (!FillConsoleOutputAttribute(
		hStdOut,
		wAttribute,
		dwLength,
		coord,
		&dwWritten))
	{
		cout << "Fill console output attribute failed." << endl;
		return GetLastError();
	}

	cout << "The fill attributes was changed." << endl;

	system("pause");

	return 0;
}
