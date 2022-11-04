#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	char lpszComLine[80];

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe, hInheritWritePipe;

	if (!CreatePipe(
		&hReadPipe,
		&hWritePipe,
		NULL,
		0))
	{
		cout << "Create pipe failed." << endl;
		system("pause");
		return GetLastError();
	}

	if (!DuplicateHandle(
		GetCurrentProcess(),
		hWritePipe,
		GetCurrentProcess(),
		&hInheritWritePipe,
		0,
		TRUE,
		DUPLICATE_SAME_ACCESS))
	{
		cout << "Duplicate handle failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	CloseHandle(hWritePipe);
	
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	wsprintf(lpszComLine, "D:\\Listing 15.1 %d", (int)hInheritWritePipe);
	
	if (!CreateProcess(
		NULL,
		lpszComLine,
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
	CloseHandle(hInheritWritePipe);
	
	for (int i = 0; i < 10; i++)
	{
		int nData;
		DWORD dwBytesRead;
		if (!ReadFile(
			hReadPipe,
			&nData,
			sizeof(nData),
			&dwBytesRead,
			NULL))
		{
			cout << "Read from the pipe failed." << endl;
			system("pause");
			return GetLastError();
		}
		cout << "The number " << nData << " is read from the pipe." << endl;
	}
	
	CloseHandle(hReadPipe);
	
	cout << "The process finished reading from the pipe." << endl;
	
	system("pause");
	
	return 0;
}