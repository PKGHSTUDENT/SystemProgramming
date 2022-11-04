#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hMailslot;
	char mailslotName[] = "\\\\.\\mailslot\\demo_mailslot";

	hMailslot = CreateFile(
		mailslotName,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	int n;
	
	cout << "Input an integer: ";
	cin >> n;
	
	DWORD dwBytesWritten;
	
	if (!WriteFile(
		hMailslot,
		&n,
		sizeof(n),
		&dwBytesWritten,
		NULL))
	{
		cerr << "Write file failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hMailslot);
		system("pause");
		return 0;
	}

	CloseHandle(hMailslot);
	
	cout << "The number is written by the client." << endl;

	system("pause");

	return 0;
}