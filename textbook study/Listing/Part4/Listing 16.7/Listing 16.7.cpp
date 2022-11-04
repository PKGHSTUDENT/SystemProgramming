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
	
	char pchInBuffer[80];
	char pchOutBuffer[80];
	
	int nMessageLength;

	cout << "Enter a name of the server machine: ";
	cin >> machineName;

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

	cin.get();
	cout << "Input a string: ";
	cin.getline(pchInBuffer, 80);
	
	nMessageLength = strlen(pchInBuffer) + 1;
	
	if (!TransactNamedPipe(
		hNamedPipe,
		&pchInBuffer,
		nMessageLength,
		&pchOutBuffer,
		sizeof(pchOutBuffer),
		&dwBytesRead,
		NULL))
	{
		cerr << "Transact named pipe failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		system("pause");
		return 0;
	}

	cout << "The sent message: "
		<< endl << '\t' << pchInBuffer << endl;
	
	cout << "The received message: "
		<< endl << '\t' << pchOutBuffer << endl;
	
	CloseHandle(hNamedPipe);
	
	system("pause");

	return 0;
}