#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hHeap;

	int* a = NULL;
	int h_size = 4096;
	int a_size = 2048;
	
	hHeap = HeapCreate(HEAP_NO_SERIALIZE, h_size, h_size);
	
	if (!hHeap)
	{
		cout << "Heap create failed." << endl;
		return GetLastError();
	}
	
	a = (int*)HeapAlloc(hHeap, NULL, a_size);
	
	if (!a)
	{
		cout << "Heap allocation failed." << endl;
		return GetLastError();
	}
	
	cout << "a[10] = " << a[10] << endl;
	
	if (!HeapFree(hHeap, NULL, a))
	{
		cout << "Heap free failed." << endl;
		return GetLastError();
	}
	
	if (!HeapDestroy(hHeap))
	{
		cout << "Heap destroy failed." << endl;
		return GetLastError();
	}

	system("pause");

	return 0;
}