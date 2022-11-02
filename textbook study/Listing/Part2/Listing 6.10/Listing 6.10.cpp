#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hOutEvent, hAddEvent;

DWORD WINAPI thread(LPVOID)
{
	for (int i = 0; i < 10; ++i)

		if (i == 4)
		{
			SetEvent(hOutEvent);
			WaitForSingleObject(hAddEvent, INFINITE);
		}

	return 0;
}

int main()
{
	HANDLE hThread;
	DWORD IDThread;

	hOutEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	if (hOutEvent == NULL)
		return GetLastError();
	
	hAddEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	if (hAddEvent == NULL)
		return GetLastError();
	
	hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);
	
	if (hThread == NULL)
		return GetLastError();
	
	WaitForSingleObject(hOutEvent, INFINITE);
	
	cout << "A half of the work is done." << endl;
	system("pause");

	SetEvent(hAddEvent);
	
	WaitForSingleObject(hThread, INFINITE);
	
	CloseHandle(hThread);
	CloseHandle(hOutEvent);
	CloseHandle(hAddEvent);

	cout << "The work is done." << endl;
	
	system("pause");
	
	return 0;
}