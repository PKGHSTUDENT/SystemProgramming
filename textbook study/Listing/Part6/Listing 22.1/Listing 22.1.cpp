#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hHeap;
	int* a = NULL;
	int size = 1000;
	
	hHeap = GetProcessHeap();
	
	if (!hHeap)
	{
		cout << "Heap create failed." << endl;
		return GetLastError();
	}
	
	a = (int*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, size * sizeof(int));
	
	cout << "a[10] = " << a[10] << endl;
	
	if (!HeapFree(hHeap, NULL, a))
	{
		cout << "Heap free failed." << endl;
		return GetLastError();
	}

	system("pause");

	return 0;
}