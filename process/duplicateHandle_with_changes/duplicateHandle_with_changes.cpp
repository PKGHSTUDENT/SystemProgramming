#define _CRT_SECURE_NO_WARNINGS


#include <Windows.h>
#include <conio.h>
#include <iostream>

using std::cout;

volatile int count;

void thread()
{
	for (;;)
	{
		count++;
		Sleep(500);
		cout << "count << " << count << "\n";
	}
}

int main()
{
	// Ссылка на исходный файл нашей программы parent_process.exe
	char lpszComLine[100] = "D:\\education\\SystemProgramming\\process\\duplicateHandle_with_changes\\parent_process.exe";
	char lpszHandle[20];

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	HANDLE hThread, hInheritThread;
	DWORD IDThread;

	cout << "Press any key to start the count-thread.\nAfter termination the thread press any key to exit.\n";
	system("pause");

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);

	if (hThread == NULL)
		return GetLastError();

	if (!DuplicateHandle(
		GetCurrentProcess(),
		hThread,
		GetCurrentProcess(),
		&hInheritThread,
		THREAD_TERMINATE,
		TRUE,
		0
	))
	{
		cout << "The handle is not duplicated.\n";
		system("pause");
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
		&pi
	))
	{
		cout << "The new process is not created.\n";
		system("pause");
		return GetLastError();
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	system("pause");

	CloseHandle(hThread);
	return 0;
}