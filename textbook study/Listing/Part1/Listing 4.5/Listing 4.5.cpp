#include <windows.h>
#include <iostream>

using namespace std;

volatile UINT _count;

void thread()
{
	for (;;)
	{
		_count++;
		Sleep(100);
	}
}
int main()
{
	char c;

	HANDLE hThread;
	DWORD IDThread;
	
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL,
		0, &IDThread);
	
	if (hThread == NULL)
		return GetLastError();
	
	for (;;)
	{
		cout << "Input 'y' to display the count or any char to exit: ";
		cin >> c;

		if (c == 'y')
			cout << "count = " << _count << endl;
		else
			ExitProcess(1);
	}
}
