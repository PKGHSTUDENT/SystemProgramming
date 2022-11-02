#include <windows.h>
#include <iostream>

using namespace std;
int main()
{
	HANDLE hStdOut;
	WORD lpAttribute[4];
	DWORD nLength = 4;
	COORD dwCoord = { 8, 0 };
	DWORD NumberOfAttrs;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "Console text attributes." << endl;
	
	system("pause");

	lpAttribute[0] = BACKGROUND_BLUE | BACKGROUND_INTENSITY |
		FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	lpAttribute[1] = BACKGROUND_GREEN | BACKGROUND_INTENSITY |
		FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	lpAttribute[2] = BACKGROUND_RED | BACKGROUND_INTENSITY |
		FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	lpAttribute[3] = BACKGROUND_GREEN | BACKGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_INTENSITY;
	
	if (!WriteConsoleOutputAttribute(hStdOut, lpAttribute,
		nLength, dwCoord, &NumberOfAttrs))
	{
		cout << "Read console output attribute failed." << endl;
		return GetLastError();
	}
	
	if (!ReadConsoleOutputAttribute(hStdOut, lpAttribute,
		nLength, dwCoord, &NumberOfAttrs))
	{
		cout << "Read console output attribute failed." << endl;
		return GetLastError();
	}
	
	cout << hex;
	cout << "Attribute[0] = " << lpAttribute[0] << endl;
	cout << "Attribute[1] = " << lpAttribute[1] << endl;
	cout << "Attribute[2] = " << lpAttribute[2] << endl;
	cout << "Attribute[3] = " << lpAttribute[3] << endl;
	
	system("pause");
	
	return 0;
}