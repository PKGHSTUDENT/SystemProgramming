#include <windows.h>
#include <iostream>

// https://learn.microsoft.com/ru-ru/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170

// Этот код не компилируется и не будет. Исправление его занимает очень много и допиливаине до
// рабочего состояния занимает достаточно времени, которое можно посвятить разбору нормальных
// примеров с официального сайта Microsoft. Поэтому, тут просто листинг кода.

using namespace std;

extern "C" __declspec(dllimport) int Add(int n);

DWORD WINAPI thread(LPVOID iNum)
{
	cout << "count from thread = " << Add((int)iNum) << endl;
	return 0;
}

int main()
{
	HANDLE hThread;
	DWORD IDThread;

	cout << "count from main = " << Add(20) << endl;
	
	hThread = CreateThread(NULL, 0, thread, (void*)10, 0, &IDThread);
	
	if (hThread == NULL)
	{
		cerr << "Create thread failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	WaitForSingleObject(hThread, INFINITE);
	
	system("pause");

	return 0;
}