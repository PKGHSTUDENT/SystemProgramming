#include <windows.h>
#include <conio.h>
#include <iostream>

#pragma warning(disable : 4996)

using namespace std;

volatile int _count;

void thread()
{
	for (;;)
	{
		_count++;
		Sleep(500);
		cout << "count = " << _count << endl;
	}
}

int main()
{
	char lpszComLine[80] = "D:\\Listing 4.8.exe ";
	char lpszHandle[20];
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hThread, hInheritThread;
	DWORD IDThread;

	system("pause");
	
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL,
		0, &IDThread);
	
	if (hThread == NULL)
		return GetLastError();
	
	if (!DuplicateHandle(
		GetCurrentProcess(),
		hThread,
		GetCurrentProcess(),
		&hInheritThread,
		0,
		TRUE, 
		DUPLICATE_SAME_ACCESS)) 
	{
		cout << "The handle is not duplicated" << endl;
		return GetLastError();
	}

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	_itoa((int)hInheritThread, lpszHandle, 10);
	strcat(lpszComLine, lpszHandle);
	
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
		cout << "The new process is not created." << endl;
		return GetLastError();
	}
	
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	system("pause");
	
	CloseHandle(hThread);
	
	return 0;
}