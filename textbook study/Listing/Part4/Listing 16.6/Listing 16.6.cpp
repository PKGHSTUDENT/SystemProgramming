#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	char machineName[80];
	char pipeName[80];

	HANDLE hNamedPipe;
	DWORD dwBytesRead;
	DWORD dwTotalBytesAvail;
	DWORD dwBytesLeftThisMessage;

	char pchMessage[80];

	cout << "Enter a name of the server machine: ";
	cin >> machineName;
	cin.get();

	wsprintf(pipeName, "\\\\%s\\pipe\\demo_pipe", machineName);

	hNamedPipe = CreateFile(
		pipeName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Connection with the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "Press any key to peek a message." << endl;
	cin.get();
	
	if (!PeekNamedPipe(
		hNamedPipe,
		pchMessage,
		sizeof(pchMessage),
		&dwBytesRead,
		&dwTotalBytesAvail,
		&dwBytesLeftThisMessage))
	{
		cerr << "Peek named pipe failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		system("pause");
		return 0;
	}

	if (dwTotalBytesAvail)
		cout << "The peeked message: "
		<< endl << '\t' << pchMessage << endl;
	else
		cout << "There is no mesage." << endl;
	
	if (!ReadFile(
		hNamedPipe,
		pchMessage,
		sizeof(pchMessage),
		&dwBytesRead,
		NULL))
	{
		cerr << "Read file failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		system("pause");
		return 0;
	}

	cout << "The client received the message from a server: "
		<< endl << '\t' << pchMessage << endl;
	
	CloseHandle(hNamedPipe);
	
	system("pause");

	return 0;
}