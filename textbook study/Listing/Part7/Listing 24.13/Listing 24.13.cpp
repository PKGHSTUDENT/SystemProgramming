#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	DWORD dwFileSize;
	long p;

	hFile = CreateFile(
		"D:\\demo_file.dat",
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
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
		return 0;
	}
	
	cout << "Old file size: " << dwFileSize << endl;
	
	dwFileSize /= 2;
	
	p = SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
	
	if (p == -1)
	{
		cerr << "Set file pointer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	
	if (!SetEndOfFile(hFile))
	{
		cerr << "Set end of file failed." << endl
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
	
	cout << "New file size: " << dwFileSize << endl;
	
	CloseHandle(hFile);
	
	system("pause");

	return 0;
}