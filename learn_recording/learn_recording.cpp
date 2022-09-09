#include <iostream>
#include <Windows.h>

using namespace std;

void CoutErrorMessage()
{
	char prefix[] = "Ошибка Win32 API";
	LPVOID lpMsgBuf;

	CharToOem(prefix, prefix);

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
	);

	CharToOem((char*)lpMsgBuf, (char*)lpMsgBuf);

	cout << prefix << (char*)lpMsgBuf << endl;

	LocalFree(lpMsgBuf);
}

int main()
{

	HANDLE hHandle = NULL;

	if (!CloseHandle(hHandle))
		CoutErrorMessage();

	char big[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	char sml[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

	CharToOem(big, big);

	CharToOem(sml, sml);

	cout << big << endl;
	cout << sml << endl;
	return 0;
}