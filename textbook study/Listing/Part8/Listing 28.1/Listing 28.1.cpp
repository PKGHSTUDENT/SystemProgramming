#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hCompletionPort; 

DWORD WINAPI thread(LPVOID)
{
	int i = 0; 
	DWORD dwNumberOfBytes; 
	ULONG ulCompletionKey; 
	LPOVERLAPPED lpOverlapped; 
	
	cout << "The thread is started." << endl;
	
	while (GetQueuedCompletionStatus(
		hCompletionPort, 
		&dwNumberOfBytes, 
		(PULONG_PTR) & ulCompletionKey,
		&lpOverlapped, 
		INFINITE)) 
		
		 
		if (ulCompletionKey == 0)
		{
			cout << endl << "The thread is finished." << endl;
			break;
		}
		else
			cout << "\tPacket: " << ++i << endl
			<< "Number of bytes: " << dwNumberOfBytes << endl
			<< "Completion key: " << ulCompletionKey << endl;
	
	return 0;
}

int main()
{
	HANDLE hFile; 
	OVERLAPPED ovl; 
	ULONG ulKey; 
	HANDLE hThread; 
	DWORD dwThreadID; 
	
	ovl.Offset = 0; 
	ovl.OffsetHigh = 0; 
	ovl.hEvent = 0; 
	
	cout << "Input a number for file key (not zero): ";
	cin >> ulKey;
	if (ulKey == 0)
	{
		cout << "The file key can't be equal to zero." << endl
			<< "Press any key to exit." << endl;
		system("pause");
		return 0;
	}
	
	hFile = CreateFile(
		"D:\\demo_file.dat", 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		OPEN_ALWAYS, 
		FILE_FLAG_OVERLAPPED, 
		NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	
	hCompletionPort = CreateIoCompletionPort(
		hFile, 
		NULL, 
		ulKey, 
		1);
	
	if (hCompletionPort == NULL)
	{
		cerr << "Create completion port failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish." << endl;
		cin.get();
		return 0;
	}
	
	hThread = CreateThread(NULL, 0, thread, NULL, 0, &dwThreadID);
	
	for (int i = 0; i < 10; ++i)
	{
		DWORD dwBytesWrite;
		DWORD dwRet;

		if (!WriteFile(
			hFile, 
			&i, 
			sizeof(i), 
			&dwBytesWrite, 
			&ovl))
		{
			dwRet = GetLastError();
			if (dwRet == ERROR_IO_PENDING)
				cout << "Write file pending." << endl;
			else
			{
				cout << "Write file failed." << endl
					<< "The last error code: " << dwRet << endl;
				system("pause");
				return 0;
			}
		}
		
		WaitForSingleObject(hFile, INFINITE);
		
		ovl.Offset += sizeof(i);
	}
	
	PostQueuedCompletionStatus(
		hCompletionPort, 
		0, 
		0, 
		NULL); 
	
	WaitForSingleObject(hThread, INFINITE);
	
	CloseHandle(hFile);
	CloseHandle(hCompletionPort);
	CloseHandle(hThread);

	cout << "The file is written." << endl;

	system("pause");

	return 0;
}