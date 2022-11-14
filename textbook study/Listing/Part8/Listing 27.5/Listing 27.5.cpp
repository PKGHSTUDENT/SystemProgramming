#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	DWORD dwFileSize;
	DWORD dwRet;
	OVERLAPPED ovl; 
	
	ovl.Offset = 0; 
	ovl.OffsetHigh = 0; 
	ovl.hEvent = 0; 

	hFile = CreateFile(
		"D:\\demo_file.dat", 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
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
		return (0);
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
			cout << "Lock file is pending." << endl;
		else
		{
			cout << "Lock file failed." << endl
				<< "The last error code: " << dwRet << endl;
			CloseHandle(hFile);
			system("pause");
			return 0;
		}
	}
	
	WaitForSingleObject(hFile, INFINITE);
	cout << "Now the file is locked." << endl
		<< "Press any key to continue." << endl;
	cin.get();
	
	if (!UnlockFileEx(hFile, 0, 0, dwFileSize, &ovl))
	{
		cerr << "Unlock file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	cout << "Now the file is unlocked." << endl;
	
	CloseHandle(hFile);

	system("pause");

	return 0;
}