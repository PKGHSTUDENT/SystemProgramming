#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	char lpszCommandLine[] = "D:\\Listing 4.1.exe p1 p2 p3";
	
	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	
	ZeroMemory(&si, sizeof(STARTUPINFO));
	
	si.cb = sizeof(STARTUPINFO);
	
	CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom);
	
	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);
	
	cout << "The new process is created." << endl;
	
	system("pause");
	return 0;
}