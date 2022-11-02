#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));

	si.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(
		NULL,
		(LPSTR)"Notepad.exe",
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi))
	{
		cout << "The mew process is not created." << endl
			<< "Check a name of the process." << endl;
		return 0;
	}
	Sleep(1000);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	system("pause");

	return 0;
}