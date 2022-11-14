#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream>

using namespace std;

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
	cout << "Initial count = " << *(DWORD*)ptr << endl;

	SleepEx(INFINITE, TRUE);

	cout << "Final count = " << *(DWORD*)ptr << endl;

	return 0;
}

int main()
{
	DWORD count = 10;

	hThread = CreateThread(NULL, 0, add, &count, 0, &IDThread);

	if (hThread == NULL)
		return GetLastError();

	Sleep(1000);

	dwRet = QueueUserAPC((PAPCFUNC)a_proc, hThread, (DWORD) & count);

	if (!dwRet)
	{
		cout << "Queue user APC failed:" << dwRet << endl;
		return 0;
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	
	system("pause");

	return 0;
}