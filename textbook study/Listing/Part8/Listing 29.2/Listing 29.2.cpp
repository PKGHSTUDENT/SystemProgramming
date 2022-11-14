#define _WIN32_WINNT 0x0400
#define _SECOND 10000000 

#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hHandle[2];

DWORD WINAPI thread(LPVOID)
{
	DWORD dwRetCode; 
	for (;;)
	{
		
		dwRetCode = WaitForMultipleObjects(2, hHandle, FALSE, INFINITE);
		
		dwRetCode -= WAIT_OBJECT_0;

		switch (dwRetCode)
		{
		case 0: 
			cout << "The timer is canceled." << endl;
			return 0;
		case 1: 
			cout << "\aThe waitable timer is signaled." << endl;
			break;
		default:
			cout << "Default statement." << endl;
			return 0;
		}
	}
}
int main()
{
	HANDLE hThread;
	DWORD IDThread;
	_int64 qwTimeInterval; 
	
	hHandle[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	if (hHandle[0] == NULL)
		return GetLastError();
	
	hHandle[1] = CreateWaitableTimer(
		NULL, 
		FALSE, 
		NULL);

	if (hHandle[1] == NULL)
		return GetLastError();
	
	qwTimeInterval = -2 * _SECOND;
	
	if (!SetWaitableTimer(
		hHandle[1], 
		(LARGE_INTEGER*)&qwTimeInterval, 
		2000, 
		NULL, 
		NULL, 
		FALSE))
	{
		cout << "Set waitable timer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);

	if (hThread == NULL)
		return GetLastError();
	
	char c;
	cout << "Input any char to cancel waitable timer." << endl;
	cin >> c;
	
	CancelWaitableTimer(hHandle[1]);
	
	SetEvent(hHandle[0]);
	
	WaitForSingleObject(hThread, INFINITE);
	
	CloseHandle(hHandle[0]);
	CloseHandle(hHandle[1]);

	system("pause");

	return 0;
}