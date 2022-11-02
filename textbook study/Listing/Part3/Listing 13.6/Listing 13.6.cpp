#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hConsoleOutput;
	CHAR lpBuffer[80];
	COORD dwReadCoord = { 0, 0 };
	DWORD nNumberOfCharsRead;
	
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput == INVALID_HANDLE_VALUE)
	{
		cout << "Get standard handle failed." << endl;
		return GetLastError();
	}

	cout << 'a' << 'b' << endl;

	if (!ReadConsoleOutputCharacter(
		hConsoleOutput,
		lpBuffer,
		2,
		dwReadCoord,
		&nNumberOfCharsRead))
	{
		cout << "Read consoleoutput character failed." << endl;
		return GetLastError();
	}

	cout << "Number of chars read: " << nNumberOfCharsRead << endl;
	cout << "Read chars: " << lpBuffer[0] << lpBuffer[1] << endl;
	
	system("pause");
	
	return 0;
}