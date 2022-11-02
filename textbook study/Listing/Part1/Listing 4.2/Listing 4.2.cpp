#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	char lpszAppName[] = "D:\\Listing 4.1.exe";
	
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	
	ZeroMemory(&si, sizeof(STARTUPINFO));
	
	si.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
	{
		cout << "The new process is not created." << endl;
		cout << "Check a name of the process." << endl;
		return 0;
	}
	cout << "The new process is created." << endl;

	WaitForSingleObject(piApp.hProcess, INFINITE);
	
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);

	system("pause");
	return 0;
}