#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	char lpszComLine1[80] = "D:\\Listing 15.5.exe";
	char lpszComLine2[80] = "D:\\Listing 15.6.exe";
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES sa;
	
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	
	if (!CreatePipe(
		&hReadPipe,
		&hWritePipe,
		&sa,
		0))

	{
		cout << "Create pipe failed." << endl;
		system("pause");
		return GetLastError();
	}

	ZeroMemory(&si, sizeof(STARTUPINFO));
	
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hReadPipe;
	si.hStdOutput = hWritePipe;
	si.hStdError = hWritePipe;
	
	if (!CreateProcess(
		NULL,
		lpszComLine1,
		NULL,
		NULL,
		TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		& si,
		&pi))
	{
		cout << "Create process failed." << endl;
		system("pause");
		return GetLastError();
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	if (!CreateProcess(
		NULL,
		lpszComLine2,
		NULL,
		NULL,
		TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi))
	{
		cout << "Create process failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	
	cout << "The clients are created." << endl;

	system("pause");

	return 0;
}