#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	char machineName[80];
	char pipeName[80];
	
	HANDLE hNamedPipe;
	
	DWORD dwFlags = PIPE_CLIENT_END |
		PIPE_TYPE_MESSAGE;
	DWORD dwOutBufferSize;
	DWORD dwInBufferSize;
	DWORD dwMaxInstances;

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

	if (!GetNamedPipeInfo(
		hNamedPipe,
		&dwFlags,
		&dwOutBufferSize,
		&dwInBufferSize,
		&dwMaxInstances))
	{
		cerr << "Get named pipe info failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "Out buffer size: " << dwOutBufferSize << endl
		<< "In buffer size: " << dwInBufferSize << endl
		<< "Max instances: " << dwMaxInstances << endl;

	CloseHandle(hNamedPipe);

	system("pause");

	return 0;
}