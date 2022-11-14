#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hFile;

	long n;
	long p;

	DWORD dwBytesRead;

	int m;

	hFile = CreateFile(
		"D:\\demo_file.dat",
		GENERIC_READ,
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
	
	cout << "Input a number from 0 to 9: ";
	cin >> n;
	
	p = SetFilePointer(hFile, n * sizeof(int), NULL, FILE_BEGIN);
	
	if (p == -1)
	{
		cerr << "Set file pointer failed." << endl
			<< "The last error code: " << GetLastError() << endl;	
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	
	cout << "File pointer: " << p << endl;
	
	if (!ReadFile(
		hFile,
		&m,
		sizeof(m),
		&dwBytesRead,
		(LPOVERLAPPED)NULL))
	{
		cerr << "Read file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}
	
	cout << "The read number: " << m << endl;
	
	CloseHandle(hFile);

	system("pause");

	return 0;
}