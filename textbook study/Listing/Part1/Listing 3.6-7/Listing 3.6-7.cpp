#include <iostream>
#include <Windows.h>

using namespace std;

// Debugging -> Debug properties for a project -> 
// Additionally -> Character set -> Use multibyte encoding

void ErrorMessageBox()
{
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);

	MessageBox(
		NULL,
		(LPCTSTR)lpMsgBuf,
		"Ошибка Win32 API",
		MB_OK | MB_ICONINFORMATION
	);

	LocalFree(lpMsgBuf);
}

int main()
{
	HANDLE hHandle = NULL;

	if (!CloseHandle(hHandle))
		ErrorMessageBox();

	system("pause");

	return 0;
}