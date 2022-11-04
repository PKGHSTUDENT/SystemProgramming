#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hMailslot;

	DWORD dwNextMessageSize;
	DWORD dwMessageCount;

	hMailslot = CreateMailslot(
		"\\\\.\\mailslot\\demo_mailslot",
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL);

	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		cerr << "Create mailslot failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The mailslot is created." << endl;

	cout << "Press any key to read messages." << endl;
	cin.get();

	if (!GetMailslotInfo(
		hMailslot,
		NULL,
		&dwNextMessageSize,
		&dwMessageCount,
		NULL))
	{
		cerr << "Get mailslot info failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	while (dwMessageCount != 0)
	{
		DWORD dwBytesRead;
		char* pchMessage;

		pchMessage = (char*) new char[dwNextMessageSize];

		if (!ReadFile(
			hMailslot,
			pchMessage,
			dwNextMessageSize,
			&dwBytesRead,
			NULL))
		{
			cerr << "Read file failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			CloseHandle(hMailslot);
			system("pause");
			return 0;
		}

		cout << "The message << " << pchMessage << " >> was read" << endl;

		if (!GetMailslotInfo(
			hMailslot,
			NULL,
			&dwNextMessageSize,
			&dwMessageCount,
			NULL))
		{
			cerr << "Get mailslot info failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			system("pause");
			return 0;
		}
		delete[] pchMessage;
	}

	CloseHandle(hMailslot);

	system("pause");

	return 0;
}