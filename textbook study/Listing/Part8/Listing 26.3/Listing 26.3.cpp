#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hSignal;
HANDLE hWait;
HANDLE hThread;

DWORD IDThread;
DWORD dwRet;

void CALLBACK a_proc(DWORD p)
{
	int n;
	DWORD* ptr = (DWORD*)p;
	cout << "The asynchronous procedure is called." << endl;

	cout << "Input integer: ";
	cin >> n;

	*ptr += n;

	cout << "The asynchronous procedure is returned." << endl;
}

DWORD WINAPI add(LPVOID ptr)
{
	DWORD dwRet;

	cout << "Initial count = " << *(DWORD*)ptr << endl;

	dwRet = SignalObjectAndWait(hSignal, hWait, 10, TRUE);

	switch (dwRet)
	{
	case WAIT_OBJECT_0:
		cout << "The event is signaled." << endl;
		break;
	case WAIT_IO_COMPLETION:
		cout << "The asynchronous procedure is done." << endl;
		break;
	case WAIT_TIMEOUT:
		cout << "Time out." << endl;
		break;
	default:
		cout << "Another case." << endl;
		break;
	}

	cout << "Final count = " << *(DWORD*)ptr << endl;

	return 0;
}

int main()
{
	char c;
	DWORD count = 10;

	cout << "Input: " << endl << "\te - to set event" << endl
		<< "\ta - to set asynchronous procedure" << endl
		<< "\tanother char - timeout" << endl
		<< "->";
	cin >> c;

	hThread = CreateThread(NULL, 0, add, &count, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
	
	hSignal = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	if (hSignal == NULL)
		return GetLastError();
	
	hWait = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	if (hWait == NULL)
		return GetLastError();
	
	WaitForSingleObject(hSignal, INFINITE);
	
	switch (c)
	{
	case 'e':
		SetEvent(hWait);
		break;
	case 'a':
		dwRet = QueueUserAPC((PAPCFUNC)a_proc, hThread, (DWORD)&count);
		if (!dwRet)
		{
			cout << "Queue user APC failed:" << dwRet << endl;
			return 0;
		}
		break;
	default:
		break;
	}
	
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	
	system("pause");

	return 0;
}