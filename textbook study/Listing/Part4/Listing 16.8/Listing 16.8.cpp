#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	char machineName[80];
	char pipeName[80];

	DWORD dwBytesRead;

	char pchInBuffer[80];
	char pchOutBuffer[80];

	int nMessageLength;

	cout << "Enter a name of the server machine: ";
	cin >> machineName;
	wsprintf(pipeName, "\\\\%s\\pipe\\demo_pipe", machineName);

	cin.get();
	cout << "Input a string: ";
	cin.getline(pchInBuffer, 80);
	
	nMessageLength = strlen(pchInBuffer) + 1;
	
	if (!CallNamedPipe(
		pipeName,
		&pchInBuffer,
		nMessageLength,
		&pchOutBuffer,
		sizeof(pchOutBuffer),
		&dwBytesRead,
		NMPWAIT_WAIT_FOREVER))
	{
		cerr << "Call named pipe failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");
		return 0;
	}

	cout << "The sent message: "
		<< endl << '\t' << pchInBuffer << endl;
	
	cout << "The received message: "
		<< endl << '\t' << pchOutBuffer << endl;
	
	system("pause");
	
	return 0;
}