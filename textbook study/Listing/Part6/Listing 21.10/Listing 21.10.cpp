#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	char c;
	char lpszCommandLine[80];
	char send[] = "This is a message.";
	char buffer[80];

	LPVOID v = (LPVOID)0x00880000;
	HANDLE hWrite, hRead;

	char WriteEvent[] = "WriteEvent";
	char ReadEvent[] = "ReadEvent";
	
	hWrite = CreateEvent(NULL, FALSE, FALSE, WriteEvent);
	hRead = CreateEvent(NULL, FALSE, FALSE, ReadEvent);
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	wsprintf(lpszCommandLine, "D:\\Listing 21.11.exe %d", (int)v);
	
	if (!CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "Create process failed." << endl;
		return GetLastError();
	}
	
	v = VirtualAllocEx(
		pi.hProcess,
		v,
		sizeof(send),
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE);
	
	if (!v)
	{
		cout << "Virtual allocation failed." << endl;
		return GetLastError();
	}

	WriteProcessMemory(pi.hProcess, v, (void*)send, sizeof(send), NULL);
	SetEvent(hWrite);
	WaitForSingleObject(hRead, INFINITE);
	ReadProcessMemory(pi.hProcess, v, (void*)buffer, sizeof(buffer), NULL);
	
	cout << buffer << endl;
	
	if (!VirtualFreeEx(pi.hProcess, v, 0, MEM_RELEASE))
	{
		cout << "Memory release failed." << endl;
		return GetLastError();
	}
	
	system("pause");
	
	return 0;
}