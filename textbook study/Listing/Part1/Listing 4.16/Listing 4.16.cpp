#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hProcess, hThread;
	BOOL bPriorityBoost;

	hProcess = GetCurrentProcess();

	if (!GetProcessPriorityBoost(hProcess, &bPriorityBoost))
	{
		cout << "Get process priority boost failed." << endl;
		return GetLastError();
	}
	cout << "The process priority boost = " << bPriorityBoost << endl;

	if (!SetProcessPriorityBoost(hProcess, TRUE))
	{
		cout << "Set process priority boost failed." << endl;
		return GetLastError();
	}

	hThread = GetCurrentThread();
	if (!GetThreadPriorityBoost(hThread, &bPriorityBoost))
	{
		cout << "Get process priority boost failed." << endl;
		return GetLastError();
	}
	cout << "The process priority boost = " << bPriorityBoost << endl;

	if (!SetThreadPriorityBoost(hThread, FALSE))
	{
		cout << "Set process priority boost failed." << endl;
		return GetLastError();
	}

	system("pause");
	return 0;
}