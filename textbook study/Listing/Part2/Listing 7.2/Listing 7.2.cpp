#include <windows.h>
#include <iostream>

using namespace std;

volatile long n;

void producer()
{
	long goods = 0;
	for (;;)
	{
		++goods;
		InterlockedCompareExchange(&n, goods, 0);
		Sleep(150);
	}
}

void consumer()
{
	long goods;
	for (;;)
	{
		Sleep(400);
		goods = n;
		InterlockedExchange((LONG*)&n, 0);
		cout << "Goods are consumed: " << goods << endl;
	}
}

int main()
{
	HANDLE hThread_p, hThread_c;
	DWORD IDThread_p, IDThread_c;

	cout << "Press any key to terminate threads." << endl;
	
	hThread_p = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producer,
		NULL, 0, &IDThread_p);
	
	if (hThread_p == NULL)
		return GetLastError();
	
	hThread_c = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer,
		NULL, 0, &IDThread_c);
	
	if (hThread_c == NULL)
		return GetLastError();

	cin.get();

	TerminateThread(hThread_p, 0);
	TerminateThread(hThread_c, 0);

	CloseHandle(hThread_c);
	CloseHandle(hThread_p);

	system("pause");

	return 0;
}