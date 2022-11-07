#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD dwOldProtect;
	
	int* a;
	const int size = 1000;
	
	a = (int*)VirtualAlloc(
		NULL,
		size * sizeof(int),
		MEM_COMMIT,
		PAGE_READONLY);
	
	if (!a)
	{
		cout << "Virtual allocation failed." << endl;
		return GetLastError();
	}
	
	__try
	{
		a[10] = 10;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD ecode = GetExceptionCode();
	
		if (ecode == EXCEPTION_ACCESS_VIOLATION)
			cout << "Access to write protected page." << endl;
		else
			cout << "Some exception." << endl;
	}
	
	if (!VirtualProtect(a, size, PAGE_READWRITE, &dwOldProtect))
	{
		cout << "Virtual protect failed." << endl;
		return GetLastError();
	}

	a[10] = 10;
	cout << "a[10] = " << a[10] << endl;

	if (!VirtualFree(a, 0, MEM_RELEASE))
	{
		cout << "Memory release failed." << endl;
		return GetLastError();
	}

	system("pause");

	return 0;
}