#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hWritePipe;

	hWritePipe = (HANDLE)atoi(argv[1]);
	
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
		Sleep(500);
	}

	CloseHandle(hWritePipe);

	cout << "The process finished writing to the pipe." << endl;

	system("pause");

	return 0;
}