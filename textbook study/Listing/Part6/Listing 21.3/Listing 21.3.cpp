#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	LPVOID lpr, lpc;

	const int Kb = 1024;
	const int size = 100;

	lpr = VirtualAlloc(
		(LPVOID)0x00880000,
		size * Kb,
		MEM_RESERVE,
		PAGE_READWRITE);

	if (!lpr)
	{
		cout << "Virtual memory reservation failed." << endl;
		return GetLastError();
	}

	cout << "Virtual memory address: " << lpr << endl;

	lpc = VirtualAlloc(
		(LPVOID)0x00888000,
		Kb,
		MEM_COMMIT,
		PAGE_READWRITE);

	if (!lpc)
	{
		cout << "Virtual memory allocation failed." << endl;
		return GetLastError();
	}

	cout << "Virtual memory address: " << lpc << endl;

	if (!VirtualFree(lpc, Kb, MEM_DECOMMIT))
	{
		cout << "Memory decommit failed." << endl;
		return GetLastError();
	}

	if (!VirtualFree(lpr, 0, MEM_RELEASE))
	{
		cout << "Memory release failed." << endl;
		return GetLastError();
	}

	system("pause");

	return 0;
}