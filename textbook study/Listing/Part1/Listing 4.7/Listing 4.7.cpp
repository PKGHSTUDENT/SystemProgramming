#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	char lpszAppName[] = "D:\\Listing 4.6.exe";
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	ZeroMemory(&si, sizeof(STARTUPINFO));
	
	si.cb = sizeof(STARTUPINFO);
	
	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "The new process is not created." << endl;
		cout << "Check a name of the process." << endl;
		return 0;
	}
	
	cout << "The new process is created." << endl;
	
	while (true)
	{
		char c;
		cout << "Input 't' to terminate the new console process: ";
		cin >> c;
		if (c == 't')
		{
			cout << "t" << endl;
			TerminateProcess(pi.hProcess, 1);
			break;
		}
	}
	
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	
	system("pause");

	return 0;
}