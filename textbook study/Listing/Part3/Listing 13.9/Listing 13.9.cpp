#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hConsoleOutput;
	CHAR_INFO lpBuffer[4];
	COORD dwBufferSize = { 2, 2 };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT ReadRegion = { 0, 0, 1, 1 };

	cout << 'a' << 'b' << endl << 'c' << 'd' << endl;
	
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (hConsoleOutput == INVALID_HANDLE_VALUE)
	{
		cout << "Get standard handle failed." << endl;
		return GetLastError();
	}
	
	if (!ReadConsoleOutput(hConsoleOutput, lpBuffer, dwBufferSize,
		dwBufferCoord, &ReadRegion))
	{
		cout << "Read console input failed." << endl;
		return GetLastError();
	}

	cout << "Read cells." << hex << endl;
	
	for (int i = 0; i < 4; ++i)
		cout << lpBuffer[i].Attributes << ' ' << lpBuffer[i].Char.AsciiChar
		<< endl;

	system("pause");
	return 0;
}