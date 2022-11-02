#include <windows.h>
#include <conio.h>
#include <iostream>

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
	char lpszComLine[80];

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sa;
	HANDLE hThread;
	DWORD IDThread;
	
	system("pause");

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	hThread = CreateThread(&sa, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0,
		&IDThread);
	
	if (hThread == NULL)
		return GetLastError();

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	wsprintf(lpszComLine, "D:\\Listing 4.8.exe %d", (int)hThread);
	
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
	
	WaitForSingleObject(hThread, INFINITE);
	
	system("pause");

	CloseHandle(hThread);
	
	return 0;
}