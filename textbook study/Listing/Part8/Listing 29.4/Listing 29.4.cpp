#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hTimer;

	hTimer = OpenWaitableTimer(
		TIMER_ALL_ACCESS,
		FALSE,
		"demo_timer");

	if (hTimer == NULL)
	{
		cout << "Open waitable timer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	WaitForSingleObject(hTimer, INFINITE);
	
	cout << "\aThe timer is signaled." << endl;
	
	CloseHandle(hTimer);
	
	system("pause");
	
	return 0;
}