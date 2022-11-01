#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
	HANDLE hStdIn;
	INPUT_RECORD ir;
	DWORD dwNumberWritten;
	DWORD dwNumber;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	
	if (hStdIn == INVALID_HANDLE_VALUE)
	{
		cout << "Get standard input handle failed." << endl;
		return GetLastError();
	}

	if (!GetNumberOfConsoleInputEvents(hStdIn, &dwNumber))
	{
		cout << "Get number of console input events failed." << endl;
		return GetLastError();
	}

	cout << "Number of console input events = " << dwNumber << endl;

	ir.EventType = KEY_EVENT;
	ir.Event.KeyEvent.bKeyDown = 0x1;
	ir.Event.KeyEvent.wRepeatCount = 1;
	ir.Event.KeyEvent.wVirtualKeyCode = 0x43;
	ir.Event.KeyEvent.wVirtualScanCode = 0x2e;
	ir.Event.KeyEvent.uChar.AsciiChar = 'c';
	ir.Event.KeyEvent.dwControlKeyState = 0x20;

	if (!WriteConsoleInput(hStdIn, &ir, 1, &dwNumberWritten))
	{
		cout << "Write console input failed." << endl;
		return GetLastError();
	}

	cout << "Write one record into the input buffer." << endl;

	if (!GetNumberOfConsoleInputEvents(hStdIn, &dwNumber))
	{
		cout << "Get number of console input events failed." << endl;
		return GetLastError();
	}
	
	cout << "Number of console input events = " << dwNumber << endl;
	cout << "Flush console input buffer." << endl;
	
	if (!FlushConsoleInputBuffer(hStdIn))
	{
		cout << "Flush console input buffer failed." << endl;
		return GetLastError();
	}
	
	if (!GetNumberOfConsoleInputEvents(hStdIn, &dwNumber))
	{
		cout << "Get number of console input events failed." << endl;
		return GetLastError();
	}
	
	cout << "Number of console input events = " << dwNumber << endl;

	system("pause");
	return 0;
}