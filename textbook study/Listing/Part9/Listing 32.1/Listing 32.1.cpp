#include <windows.h>
#include <iostream>

using namespace std;

DWORD thread(void)
{
	char c;
	DWORD dwFirstTlsIndex, dwPrevTlsIndex, dwNextTlsIndex;
	
	dwFirstTlsIndex = TlsAlloc();
	
	if (dwFirstTlsIndex == -1)
	{
		cerr << "Tls allocation failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	dwPrevTlsIndex = dwFirstTlsIndex;
	
	for (;;)
	{
		cout << "Alloc tls index = " << dwPrevTlsIndex << endl;
		
		Sleep(50);
		
		dwNextTlsIndex = TlsAlloc();
		
		if (dwNextTlsIndex == -1)
			break;
		
		if (!TlsSetValue(dwPrevTlsIndex, (LPVOID)dwNextTlsIndex))
		{
			cerr << "Tls set value failed." << endl;
			system("pause");
			return GetLastError();
		}
		
		dwPrevTlsIndex = dwNextTlsIndex;
	}
	
	system("pause");
	
	dwPrevTlsIndex = dwFirstTlsIndex;
	
	for (;;)
	{
		cout << "Free tls index = " << dwPrevTlsIndex << endl;
		Sleep(50);
		
		dwNextTlsIndex = (DWORD)TlsGetValue(dwPrevTlsIndex);
		
		if (!dwNextTlsIndex)
			break;

		if (!TlsFree(dwPrevTlsIndex))
		{
			cerr << "Tls free failed." << endl;
			system("pause");
			return GetLastError();
		}
		dwPrevTlsIndex = dwNextTlsIndex;
	}
	
	system("pause");

	return 0;
}

int main()
{
	HANDLE hThread;
	DWORD IDThread;
	
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread,
		NULL, 0, &IDThread);
	
	if (hThread == NULL)
	{
		cerr << "Create thread failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	WaitForSingleObject(hThread, INFINITE);
	
	CloseHandle(hThread);

	system("pause");

	return 0;
}