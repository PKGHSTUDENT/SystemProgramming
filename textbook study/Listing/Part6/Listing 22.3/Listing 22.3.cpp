#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hHeap;

	int* a = NULL;

	// The value 4096 is large enough and the system (on my device at least)
	// cannot allocate that much virtual memory for this heap
	int size = 1024;

	hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, size);
	
	if (!hHeap)
	{
		cout << "Heap create failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	a = (int*)HeapAlloc(hHeap, NULL, size * sizeof(int));
	
	if (!a)
	{
		cout << "Heap allocation failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	if (!HeapDestroy(hHeap))
	{
		cout << "Heap destroy failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	cout << "Tadam!" << endl;
	system("pause");

	return 0;
}