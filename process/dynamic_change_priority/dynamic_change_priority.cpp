#include <Windows.h>
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
		system("pause");

		return GetLastError();
	}

	cout << "The process priority boost = " << bPriorityBoost << endl;

	if (!SetProcessPriorityBoost(hProcess, TRUE))
	{
		cout << "SetProcess priority boost failed" << endl;
		system("pause");
		return GetLastError();
	}

	hProcess = GetCurrentProcess();
	
	if (!GetProcessPriorityBoost(hProcess, &bPriorityBoost))
	{
		cout << "Get process priority boost failed." << endl;
		system("pause");

		return GetLastError();
	}

	cout << "The process priority boost = " << bPriorityBoost << endl;

	if (!SetProcessPriorityBoost(hProcess, FALSE))
	{
		cout << "SetProcess priority boost failed" << endl;
		system("pause");
		return GetLastError();
	}

	system("pause");

	return 0;
}
