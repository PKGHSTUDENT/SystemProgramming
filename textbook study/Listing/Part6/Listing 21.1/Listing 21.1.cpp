#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* a;
	const int size = 1000;
	
	a = (int*)VirtualAlloc(
		NULL,
		size * sizeof(int),
		MEM_COMMIT,
		PAGE_READWRITE);

	if (!a)
	{
		cout << "Virtual allocation failed." << endl;
		return GetLastError();
	}
	
	cout << "Virtual memory address: " << a << endl;
	
	if (!VirtualFree(a, 0, MEM_RELEASE))
	{
		cout << "Memory release failed." << endl;
		return GetLastError();
	}

	system("pause");

	return 0;
}