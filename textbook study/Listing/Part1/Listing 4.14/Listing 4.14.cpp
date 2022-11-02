#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hProcess;
	DWORD dwPriority;

	hProcess = GetCurrentProcess();

	dwPriority = GetPriorityClass(hProcess);
	
	cout << "The priority of the process = " << dwPriority << endl;
	
	if (!SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS))
	{
		cout << "Set priority class failed." << endl;
		return GetLastError();
	}

	dwPriority = GetPriorityClass(hProcess);
	
	cout << "The priority of the process = " << dwPriority << endl;

	if (!SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
	{
		cout << "Set priority class failed." << endl;
		return GetLastError();
	}

	dwPriority = GetPriorityClass(hProcess);
	cout << "The priority of the process = " << dwPriority << endl;
	
	system("pause");
	
	return 0;
}