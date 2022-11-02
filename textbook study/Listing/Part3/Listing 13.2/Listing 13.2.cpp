#include <windows.h>

HANDLE hStdOut, hStdIn;

int main(void)
{
	LPSTR lpszPrompt1 = (LPSTR)"Input 'q' and press Enter to exit.\n";
	LPSTR lpszPrompt2 = (LPSTR)"Input string and press Enter:\n";
	
	CHAR chBuffer[80];
	DWORD cRead, cWritten;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (hStdIn == INVALID_HANDLE_VALUE || hStdOut == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Get standard handle failed", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	
	if (!WriteFile(
		hStdOut,
		lpszPrompt1, 
		lstrlen(lpszPrompt1),
		&cWritten,
		NULL))
	{
		MessageBox(NULL, "Write file failed", "Win32 API error",
			MB_OK | MB_ICONINFORMATION);
		return GetLastError();
	}
	
	for (;;)
	{
		if (!WriteFile(
			hStdOut,
			lpszPrompt2,
			lstrlen(lpszPrompt2),
			&cWritten,
			NULL))
		{
			MessageBox(NULL, "Write file failed", "Win32 API error",
				MB_OK | MB_ICONINFORMATION);
			return GetLastError();
		}
	
		if (!ReadFile(
			hStdIn,
			chBuffer,
			80,
			&cRead,
			NULL))
		{
			MessageBox(NULL, "Write file failed", "Win32 API error",
				MB_OK | MB_ICONINFORMATION);
			return GetLastError();
		}
		
		if (chBuffer[0] == 'q')
		{
			system("pause");
			return 1;
		}
	}

	return 0;
}