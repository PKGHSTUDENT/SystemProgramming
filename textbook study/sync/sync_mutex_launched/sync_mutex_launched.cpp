﻿#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hMutex;
	int i, j;

	hMutex = OpenMutex(SYNCHRONIZE, FALSE, "DemoMutex");
	if (hMutex == NULL)
	{
		cout << "Open mutex failed." << endl;
		system("pause");

		return GetLastError();
	}

	for (j = 10; j < 20; j++)
	{
		WaitForSingleObject(hMutex, INFINITE);
		for (i = 0; i < 10; i++)
		{
			cout << j << ' ' << flush;
			Sleep(5);
		}
		cout << endl;

		ReleaseMutex(hMutex);
	}
	CloseHandle(hMutex);

	return 0;
}