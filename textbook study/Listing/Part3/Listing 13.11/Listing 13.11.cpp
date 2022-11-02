#include <windows.h>

HANDLE hStdOut, hStdIn;

int main(void)
{
	LPSTR lpszPrompt1 = (LPSTR)"Input ESC and press Enter to exit.\n";
	LPSTR lpszPrompt2 = (LPSTR)"Input string and press Enter:\n";
	CHAR chBuffer[80];
	DWORD cRead, cWritten;
	DWORD dwOldMode, dwNewMode;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (hStdIn == INVALID_HANDLE_VALUE || hStdOut == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Get standard handle failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	if (!GetConsoleMode(hStdIn, &dwOldMode))
	{
		MessageBox(NULL, "Get console mode failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	
	dwNewMode = dwOldMode & ~ENABLE_ECHO_INPUT;
	
	if (!SetConsoleMode(hStdIn, dwNewMode))
	{
		MessageBox(NULL, "Set console mode failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	
	if (!WriteConsole(
		hStdOut,
		lpszPrompt1,
		lstrlen(lpszPrompt1),
		&cWritten,
		NULL))
	{
		MessageBox(NULL, "Write file failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	
	for (;;)
	{
		if (!WriteConsole(
			hStdOut,
			lpszPrompt2,
			lstrlen(lpszPrompt2),
			& cWritten,
			NULL))
		{
			MessageBox(NULL, "Write file failed.", "Win32 API error",
				MB_OK | MB_ICONINFORMATION);
			return GetLastError();
		}

		if (!ReadConsole(
			hStdIn,
			chBuffer,
			80,
			&cRead,
			NULL))
		{
			MessageBox(NULL, "Read file failed.", "Win32 API error",
				MB_OK | MB_ICONINFORMATION);
			return GetLastError();
		}
		
		if (chBuffer[0] == '\033')
			return 1;

		if (!WriteConsole(
			hStdOut,
			chBuffer,
			cRead,
			&cWritten,
			NULL))
		{
			MessageBox(NULL, "Write file failed.", "Win32 API error",
				MB_OK | MB_ICONINFORMATION);
			return GetLastError();
		}
	}
	return 0;
}