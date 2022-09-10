#include <iostream>
#include <Windows.h>
#include <conio.h>

using std::cout;

int main()
{
	// Перемещаем скомпилированный файл в каталог, из которого запускается приложение.
	char lpszCommandLine[] = "process_output_info.exe p1 p2 p3";
	

	STARTUPINFO si;
	PROCESS_INFORMATION piCom;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom);

	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);

	cout << "The new process is created.\n";

	system("pause");
	return 0;
}