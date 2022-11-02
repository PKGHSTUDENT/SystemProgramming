#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	char ConsoleTitleBuffer[80];

	DWORD dwBufferSize = 80;
	DWORD dwTitleSize;

	dwTitleSize = GetConsoleTitle(ConsoleTitleBuffer, dwBufferSize);

	cout << "Title length = " << dwTitleSize << endl;
	cout << "The window title = " << ConsoleTitleBuffer << endl;
	cout << "Input new title: ";
	cin.getline(ConsoleTitleBuffer, 80);

	if (!SetConsoleTitle(ConsoleTitleBuffer))
		cout << "Set console title failed." << endl;
	cout << "The title was changed." << endl;

	system("pause");

	return 0;
}