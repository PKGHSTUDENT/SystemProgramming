#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	HANDLE hEndWrite; 
	OVERLAPPED ovl; 
	
	hEndWrite = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	if (hEndWrite == NULL)
		return GetLastError();
	
	ovl.Offset = 0; 
	ovl.OffsetHigh = 0; 
	ovl.hEvent = hEndWrite; 

	hFile = CreateFile(
		"D:\\demo_file.dat", 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		OPEN_ALWAYS, 
		FILE_FLAG_OVERLAPPED, 
		NULL 
	);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hEndWrite);
		system("pause");
		return 0;
	}
	
	for (int i = 0; i < 10; ++i)
	{
		DWORD dwBytesWrite;
		DWORD dwNumberOfBytesTransferred;
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
				return 0;
			}
		}
		
		if (!GetOverlappedResult(
			hFile, 
			&ovl, 
			&dwNumberOfBytesTransferred, 
			FALSE))
		{
			cout << "Get overlapped result failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			
			return 0;
		}
		else
			cout << "Number of bytes transferred: "
			<< dwNumberOfBytesTransferred << endl;
		
		WaitForSingleObject(hEndWrite, INFINITE);
		
		ovl.Offset += sizeof(i);
	}
	
	CloseHandle(hFile);
	CloseHandle(hEndWrite);
	
	cout << "The file is written." << endl;

	system("pause");
	
	return 0;
}