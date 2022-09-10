#include <Windows.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

volatile UINT count;

void thread()
{
	for (;;)
	{
		count++;
		Sleep(100);
	}
}

int main()
{
	char c;
	HANDLE hThread;
	DWORD IDThread;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);

	if (hThread == NULL)
		return GetLastError();

	for (;;)
	{
		char buf;
		cout << "Input 'y' to display the count or any char to exit: ";
		cin >> buf;
		if (buf == 'y')
			cout << "count = " << count << endl;
		else
			ExitProcess(1);
	}
	return 0;
}