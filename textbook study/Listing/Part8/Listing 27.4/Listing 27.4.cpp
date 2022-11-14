#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile; 
	HANDLE hEndRead; 
	OVERLAPPED ovl; 
	
	hEndRead = CreateEvent(NULL, FALSE, FALSE, NULL);

	if (hEndRead == NULL)
		return GetLastError();

	ovl.Offset = 0; 
	ovl.OffsetHigh = 0; 
	ovl.hEvent = hEndRead; 
	
	hFile = CreateFile(
		"D:\\demo_file.dat", 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hEndRead);
		system("pause");
		return 0;
	}
	
	for (;;)
	{
		DWORD dwBytesRead;
		DWORD dwRet;
		int n;
		
		if (!ReadFile(
			hFile, 
			&n, 
			sizeof(n), 
			&dwBytesRead, 
			&ovl 
		))
		{
			switch (dwRet = GetLastError())
			{
			case ERROR_IO_PENDING:
				cout << "Read file pending." << endl;
				break;
			case ERROR_HANDLE_EOF:
				cout << endl << "End of the file." << endl;
				cout << "The file is read." << endl;
				
				CloseHandle(hFile);
				CloseHandle(hEndRead);
				return 1;
			default:
				cout << "Read file failed." << endl
					<< "The last error code: " << dwRet << endl;
				
				CloseHandle(hFile);
				CloseHandle(hEndRead);
				return 0;
			}
		}
		
		WaitForSingleObject(hEndRead, INFINITE);
		
		cout << n << ' ';
		
		ovl.Offset += sizeof(n);
		system("pause");
	}
}