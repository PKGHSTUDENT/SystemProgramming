#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hStdOutOld, hStdOutNew;
	DWORD dwWritten;

	hStdOutNew = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	if (hStdOutNew == INVALID_HANDLE_VALUE)
	{
		cout << "Create console screen buffer failed." << endl;
		return GetLastError();
	}

	hStdOutOld = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("pause");

	if (!SetConsoleActiveScreenBuffer(hStdOutNew))
	{
		cout << "Set new console active screen buffer failed." << endl;
		return GetLastError();
	}

	char text[] = "This is a new screen buffer.";
	
	if (!WriteConsole(hStdOutNew, text, sizeof(text), &dwWritten, NULL))
		cout << "Write console output character failed." << endl;
	
	char str[] = "\nPress any key to set old screen buffer.";
	
	if (!WriteConsole(hStdOutNew, str, sizeof(str), &dwWritten, NULL))
		cout << "Write console output character failed" << endl;

	if (!SetConsoleActiveScreenBuffer(hStdOutOld))
	{
		cout << "Set old console active screen buffer failed." << endl;
		return GetLastError();
	}
	
	cout << "This is an old console screen buffer." << endl;
	
	CloseHandle(hStdOutNew);
	
	system("pause");

	return 0;
}