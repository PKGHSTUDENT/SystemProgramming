#include <Windows.h>
#include <iostream>
using namespace std;

DWORD WINAPI thread(LPVOID)
{
	int i, j;

	for (j = 0; j < 10; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			cout << j << ' ' << flush;
			Sleep(17);
		}
		cout << endl;
	}
	return 0;
}

int main()
{
	int i, j;
	HANDLE hThread;
	DWORD IDThread;

	hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();

	for (j = 10; j < 20; ++j)
	{
		for (i = 0; i < 10; ++i)
		{
			cout << j << ' ' << flush;
			Sleep(17);
		}
		cout << endl;
	}

	WaitForSingleObject(hThread, INFINITE);

	system("pause");
	return 0;
}