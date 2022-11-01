#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
	HANDLE hMutex;
	char lpszAppName[] = "D:\\education\\SystemProgramming\\sync\\sync_mutex\\sync_mutex_launched.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	hMutex = CreateMutex(NULL, FALSE, "DemoMutex");
	if (hMutex == NULL)
	{
		cout << "Create mutex failed" << endl;
		system("pause");

		return GetLastError();
	}

	ZeroMemory(&si, sizeof(STARTUPINFO));

	si.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi))
	{
		cout << "The new process is not created." << endl;
		system("pause");

		return GetLastError();
	}

	for (int j = 0; j < 10; ++j)
	{
		WaitForSingleObject(hMutex, INFINITE);
		for (int i = 0; i < 10; i++)
		{
			cout << j << ' ' << flush;
			Sleep(10);
		}
		cout << endl;
		ReleaseMutex(hMutex);
	}

	CloseHandle(hMutex);
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return 0;
}