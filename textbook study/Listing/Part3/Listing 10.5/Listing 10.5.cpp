#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	if (!AllocConsole())
	{
		MessageBox(NULL,
			"Console allocation failed", "Error Win32 API",
			MB_OK | MB_ICONINFORMATION);
		return 0;
	}

	cout << "I am created." << endl;
	if (!FreeConsole())
	{
		cout << "Free console failed." << endl;
		system("pause");
	}

	system("pause");
	return 0;
}