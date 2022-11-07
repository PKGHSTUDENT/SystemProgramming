#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	BYTE* a, * b;

	const int size = 10000;
	const int shift = 5000;
	
	MEMORY_BASIC_INFORMATION mbi;
	DWORD mbi_size = sizeof(MEMORY_BASIC_INFORMATION);
	
	a = (BYTE*)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
	
	if (!a)
	{
		cout << "Virtual allocation failed." << endl;
		return GetLastError();
	}
	
	b = a + shift;
	
	if (mbi_size != VirtualQuery(b, &mbi, mbi_size))
	{
		cout << "Virual query failed." << endl;
		return GetLastError();
	}
	
	cout << "Base address: " << mbi.BaseAddress << endl;
	cout << "Allocation base: " << mbi.AllocationBase << endl;
	cout << "Allocation protect: " << mbi.AllocationProtect << endl;
	cout << "Region size: " << mbi.RegionSize << endl;
	cout << "State: " << mbi.State << endl;
	cout << "Protect: " << mbi.Protect << endl;
	cout << "Type: " << mbi.Type << endl;
	
	if (!VirtualFree(a, 0, MEM_RELEASE))
	{
		cout << "Memory release failed." << endl;
		return GetLastError();
	}

	system("pause");

	return 0;
}