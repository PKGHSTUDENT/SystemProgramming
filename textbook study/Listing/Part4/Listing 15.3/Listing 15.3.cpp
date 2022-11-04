#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hWritePipe, hReadPipe;
	HANDLE hEnableRead;
	
	char lpszEnableRead[] = "EnableRead";
	
	hEnableRead = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszEnableRead);
	
	hWritePipe = (HANDLE)atoi(argv[1]);
	hReadPipe = (HANDLE)atoi(argv[2]);
	
	system("pause");

	for (int i = 0; i < 10; i++)
	{
		DWORD dwBytesWritten;
		if (!WriteFile(
			hWritePipe,
			&i,
			sizeof(i),
			&dwBytesWritten,
			NULL))
		{
			cout << "Write to file failed." << endl;
			system("pause");
			return GetLastError();
		}
		cout << "The number " << i << " is written to the pipe." << endl;
	}
	cout << "The process finished writing to the pipe." << endl;
	
	WaitForSingleObject(hEnableRead, INFINITE);
	
	for (int j = 0; j < 10; j++)
	{
		int nData;
		DWORD dwBytesRead;
		if (!ReadFile(
			hReadPipe,
			&nData,
			sizeof(nData),
			&dwBytesRead,
			NULL))
		{
			cout << "Read from the pipe failed." << endl;
			system("pause");
			return GetLastError();
		}
		cout << "The number " << nData << " is read from the pipe." << endl;
	}
	cout << "The process finished reading from the pipe." << endl;
	
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEnableRead);

	system("pause");

	return 0;
}