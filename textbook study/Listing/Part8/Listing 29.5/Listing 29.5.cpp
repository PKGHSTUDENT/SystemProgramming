#define _WIN32_WINNT 0x0400
#define _SECOND 10000000 

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

VOID CALLBACK completion_proc(LPVOID lpArg,
	DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{

	cout << "\aThe timer is signaled." << endl;

	cout << "Arguments: " << (char*)lpArg << endl
		<< "Timer low value: " << dwTimerLowValue << endl
		<< "Timer high value: " << dwTimerHighValue << endl;
}

int main()
{
	HANDLE hTimer;
	_int64 qwTimeInterval;


	char buff[] = "Demo parameters.";
	LPVOID lpArgToCompletionRoutine = buff;

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

	if (hTimer == NULL)
		return GetLastError();

	qwTimeInterval = -1 * _SECOND;

	if (!SetWaitableTimer(
		hTimer,
		(LARGE_INTEGER*)&qwTimeInterval,
		0,
		completion_proc,
		lpArgToCompletionRoutine,
		FALSE))
	{
		cout << "Set waitable timer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		return 0;
	}

	SleepEx(INFINITE, TRUE);

	CloseHandle(hTimer);

	system("pause");

	return 0;
}