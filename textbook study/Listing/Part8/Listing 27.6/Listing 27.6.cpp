#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile; 
	HANDLE hEndLock;
	DWORD dwFileSize;
	DWORD dwRet;
	OVERLAPPED ovl; 
	
	hEndLock = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hEndLock == NULL)
		return GetLastError();
	
	ovl.Offset = 0; 
	ovl.OffsetHigh = 0; 
	ovl.hEvent = hEndLock; 
	
	hFile = CreateFile(
		"D:\\demo_file.dat", 
		GENERIC_WRITE, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	
	
	dwFileSize = GetFileSize(hFile, NULL);
	
	if (dwFileSize == -1)
	{
		cerr << "Get file size failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	
	if (!LockFileEx(
		hFile, 
		LOCKFILE_EXCLUSIVE_LOCK, 
		0, 
		0, dwFileSize, 
		&ovl)) 
	{
		dwRet = GetLastError();
		if (dwRet == ERROR_IO_PENDING)
			cout << "The lock file is pending." << endl;
		else
		{
			cout << "Lock file failed." << endl
				<< "The last error code: " << dwRet << endl;
			CloseHandle(hFile);
			CloseHandle(hEndLock);
			return 0;
		}
	}
	
	WaitForSingleObject(hEndLock, INFINITE);
	
	cout << "Now the file is locked." << endl
		<< "Press any key to continue." << endl;
	cin.get();
	
	if (!UnlockFileEx(hFile, 0, 0, dwFileSize, &ovl))
	{
		cerr << "Unlock file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		CloseHandle(hEndLock);
		system("pause");
		return 0;
	}
	
	cout << "Now the file is unlocked." << endl;
	
	CloseHandle(hFile);
	CloseHandle(hEndLock);

	system("pause");
	return 0;
}