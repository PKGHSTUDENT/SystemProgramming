#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hThread;
	
	char c;
	
	hThread = (HANDLE)atoi(argv[1]);
	
	while (true)
	{
		cout << "Input 't' to terminate the thread:";
		cin >> c;
		if (c == 't')
		{
			cout << "t" << endl;
			break;
		}
	}
	
	TerminateThread(hThread, 0);
	
	CloseHandle(hThread);
	
	system("pause");
	
	return 0;
}