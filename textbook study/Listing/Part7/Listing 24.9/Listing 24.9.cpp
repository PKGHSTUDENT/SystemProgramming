#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	HANDLE hFile;

	int n;

	LARGE_INTEGER p;
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

	// I love f#cking crutches :))
	LARGE_INTEGER offset;
	offset.QuadPart = (sizeof(int) * n);

	
	if (!SetFilePointerEx(hFile, offset, &p, FILE_BEGIN))
	{
		cerr << "Set file pointer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		system("pause");
		return 0;
	}

	cout << "File pointer: " << p.QuadPart << endl;
	
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