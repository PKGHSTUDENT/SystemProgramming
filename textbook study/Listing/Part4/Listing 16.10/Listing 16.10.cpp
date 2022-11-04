#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	char machineName[80];
	char pipeName[80];

	HANDLE hNamedPipe;
	DWORD dwState;
	DWORD dwCurInstances;
	DWORD dwMaxCollectionCount;
	DWORD dwCollectDataTimeout;
	TCHAR chUserName[255];

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

	if (!GetNamedPipeHandleState(
		hNamedPipe,
		&dwState,
		&dwCurInstances,
		&dwMaxCollectionCount,
		&dwCollectDataTimeout,
		chUserName,
		255))
	{
		cerr << "Get named pipe handle state failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "Collection data timeout: " << dwCollectDataTimeout << endl;
	
	dwCollectDataTimeout = 100;
	
	if (!SetNamedPipeHandleState(
		hNamedPipe,
		NULL,
		NULL,
		&dwCollectDataTimeout))
	{
		cerr << "Set named pipe handle state failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	GetNamedPipeHandleState(
		hNamedPipe,
		&dwState,
		&dwCurInstances,
		&dwMaxCollectionCount,
		&dwCollectDataTimeout,
		chUserName,
		255);

	cout << "Collection data timeout: " << dwCollectDataTimeout << endl;
	
	CloseHandle(hNamedPipe);
	
	system("pause");
	
	return 0;
}