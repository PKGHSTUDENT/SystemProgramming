#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;
int main()
{
	HANDLE hThread;
	DWORD dwPriority;

	hThread = GetCurrentThread();

	
	dwPriority = GetThreadPriority(hThread);
	cout << "The priority level of the thread = " << dwPriority << endl;
	
	if (!SetThreadPriority(hThread, THREAD_PRIORITY_LOWEST))
	{
		cout << "Set thread priority failed." << endl;
		return GetLastError();
	}
	
	dwPriority = GetThreadPriority(hThread);
	cout << "The priority level of the thread = " << dwPriority << endl;
	
	if (!SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST))
	{
		cout << "Set thread priority failed." << endl;
		return GetLastError();
	}
	
	dwPriority = GetThreadPriority(hThread);
	cout << "The priority level of the thread = " << dwPriority << endl;

	system("pause");

	return 0;
}