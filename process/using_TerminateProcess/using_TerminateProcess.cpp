#include <Windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	// Перемещаем в папку к исходнику скоммпиированный файл и запускаем.
	char lpszAppName[] = "endless_cycle.exe";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "The new process is not created.\n";
		cout << "Check a name of the process.\n";
		return 0;
	}

	cout << "The new process is created.\n";

	while (true)
	{
		char c;

		cout << "Input 't' to terminate the new console process: ";
		cin >> c;
		if (c == 't')
		{
			cout << "t\n";
			TerminateProcess(pi.hProcess, 1);
			break;
		}
	}

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);



	return 0;
}