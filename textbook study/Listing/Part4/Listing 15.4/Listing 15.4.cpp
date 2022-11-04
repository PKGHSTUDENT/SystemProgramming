#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	char lpszComLine[80];
	char lpszEnableRead[] = "EnableRead";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	HANDLE hEnableRead;
	HANDLE hWritePipe, hReadPipe;

	SECURITY_ATTRIBUTES sa;

	hEnableRead = CreateEvent(NULL, FALSE, FALSE, lpszEnableRead);

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
	
	wsprintf(lpszComLine, "D:\\Listing 15.3.exe %d %d",
		(int)hWritePipe, (int)hReadPipe);
	
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
	cout << "The process finished reading from the pipe." << endl;
	
	SetEvent(hEnableRead);
	
	for (int j = 10; j < 20; j++)
	{
		DWORD dwBytesWritten;
		if (!WriteFile(
			hWritePipe,
			&j,
			sizeof(j),
			&dwBytesWritten,
			NULL))
		{
			cout << "Write to file failed." << endl;
			system("pause");
			return GetLastError();
		}
		cout << "The number " << j << " is written to the pipe." << endl;
	}
	
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(hEnableRead);

	cout << "The process finished writing to the pipe." << endl;
	
	system("pause");
	return 0;
}