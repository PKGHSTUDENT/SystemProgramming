#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hMailslot;
	DWORD dwReadTimeout;

	hMailslot = CreateMailslot(
		"\\\\.\\mailslot\\demo_mailslot",
		0,
		0,
		NULL);

	if (hMailslot == INVALID_HANDLE_VALUE)
	{
		cerr << "Create mailslot failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The mailslot is created." << endl;
	
	if (!GetMailslotInfo(
		hMailslot,
		NULL,
		NULL,
		NULL,
		&dwReadTimeout))
	{
		cerr << "Get mailslot info failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "Read timeout: " << dwReadTimeout << endl;
	
	if (!SetMailslotInfo(
		hMailslot,
		3000))
	{
		cerr << "Set mailslot info failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	if (!GetMailslotInfo(
		hMailslot,
		NULL,
		NULL,
		NULL,
		&dwReadTimeout))
	{
		cerr << "Get mailslot info failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}
	cout << "Read timeout: " << dwReadTimeout << endl;

	CloseHandle(hMailslot);

	system("pause");

	return 0;
}