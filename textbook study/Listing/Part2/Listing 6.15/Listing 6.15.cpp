#include <windows.h>
#include <iostream>

using namespace std;

volatile int a[10];

HANDLE hSemaphore;

DWORD WINAPI thread(LPVOID)
{
	for (int i = 0; i < 10; i++)
	{
		a[i] = i + 1;

		ReleaseSemaphore(hSemaphore, 1, NULL);

		Sleep(500);
	}

	return 0;
}

int main()
{
	int i;
	HANDLE hThread;
	DWORD IDThread;

	cout << "An initial state of the array: ";
	for (i = 0; i < 10; i++)
		cout << a[i] << ' ';
	cout << endl;

	hSemaphore = CreateSemaphore(NULL, 0, 10, NULL);

	if (hSemaphore == NULL)
		return GetLastError();

	hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);

	if (hThread == NULL)
		return GetLastError();

	cout << "A final state of the array: ";
	for (i = 0; i < 10; i++)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		cout << a[i] << " \a" << flush;
	}
	cout << endl;

	CloseHandle(hSemaphore);
	CloseHandle(hThread);

	system("pause");

	return 0;
}