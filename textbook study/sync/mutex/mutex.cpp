#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
	char lpszAppName[] = "D:\\education\\SystemProgramming\\sync\\mutex\\mutex_thread_1.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi))
	{
		cout << "The new process is not created." << endl;
		return GetLastError();
	}

	for (int j = 0; j < 10; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			cout << j << ' ' << flush;
			Sleep(10);
		}
		cout << endl;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return 0;
}