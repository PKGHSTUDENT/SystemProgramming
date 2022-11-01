#include <windows.h>
#include <iostream>
using namespace std;


int main()
{
	DWORD dwNumber;

	if (!GetNumberOfConsoleMouseButtons(&dwNumber))
	{
		cout << "Get number of console mouse buttons failed." << endl;
		return GetLastError();
	}

	cout << "Number of console mouse buttons = " << dwNumber << endl;

	system("pause");
	return 0;
}