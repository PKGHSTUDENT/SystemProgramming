#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;
	DWORD dwFileSize;

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
	
	if (!LockFile(hFile, 0, 0, dwFileSize, 0))
	{
		cerr << "Lock file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	
	cout << "Now the file is locked." << endl
		<< "Press any key to continue." << endl;
	cin.get();
	
	if (!UnlockFile(hFile, 0, 0, dwFileSize, 0))
	{
		cerr << "Unlock file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	
	cout << "Now the file is unlocked." << endl
		<< "Press any key to continue." << endl;
	cin.get();
	
	CloseHandle(hFile);

	system("pause");

	return 0;
}