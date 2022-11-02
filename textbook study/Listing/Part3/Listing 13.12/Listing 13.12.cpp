#include <windows.h>

HANDLE hStdOut, hStdIn;

int GoToNewLine(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT srScroll;
	SMALL_RECT srClip;
	COORD coord;
	CHAR_INFO ci;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		MessageBox(NULL, "Get console screen buffer info failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	
	csbi.dwCursorPosition.X = 0;
	
	if ((csbi.dwCursorPosition.Y + 1) < csbi.dwSize.Y)
		csbi.dwCursorPosition.Y += 1;
	else
	{
		srScroll.Left = 0;
		srScroll.Top = 1;
		srScroll.Right = csbi.dwSize.X;
		srScroll.Bottom = csbi.dwSize.Y;
		
		srClip.Left = 0;
		srClip.Top = 0;
		srClip.Right = csbi.dwSize.X;
		srClip.Bottom = csbi.dwSize.Y;
		
		coord.X = 0;
		coord.Y = 0;
		
		ci.Attributes = csbi.wAttributes;
		ci.Char.AsciiChar = ' ';
		
		if (!ScrollConsoleScreenBuffer(
			hStdOut,
			&srScroll,
			&srClip,
			coord,
			&ci))
		{
			MessageBox(NULL, "Set console window info failed.", "Win32 API error",
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
	}

	if (!SetConsoleCursorPosition(hStdOut, csbi.dwCursorPosition))
	{
		MessageBox(NULL, "Set console cursor position failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	return 1;
}

int main(void)
{
	LPSTR lpszPrompt = (LPSTR)"Press ESC to exit.\n";
	CHAR c;

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
	
	dwNewMode = dwOldMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	
	if (!SetConsoleMode(hStdIn, dwNewMode))
	{
		MessageBox(NULL, "Set console mode failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	
	if (!WriteFile(
		hStdOut,
		lpszPrompt,
		lstrlen(lpszPrompt),
		&cWritten,
		NULL))
	{
		MessageBox(NULL, "Write file failed.", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	
	for (;;)
	{
		if (!ReadFile(hStdIn, &c, 1, &cRead, NULL))
		{
			MessageBox(NULL, "Write file failed.", "Win32 API error",
				MB_OK | MB_ICONINFORMATION);
			return GetLastError();
		}

		switch (c)
		{
		case '\r':
			if (!GoToNewLine())
			{
				MessageBox(NULL, "Go to a new line failed.", "Win32 API error",
					MB_OK | MB_ICONINFORMATION);
				return GetLastError();
			}
			break;
		case '\033':
			return 1;
		default:
			if (!WriteFile(hStdOut, &c, cRead, &cWritten, NULL))
			{
				MessageBox(NULL, "Write file failed.", "Win32 API error",
					MB_OK | MB_ICONINFORMATION);
				return GetLastError();
			}
		}
	}
	return 0;
}