#include <windows.h>
#include <iostream>

using namespace std;

int main()
{

	HANDLE hHeap;
	int* a = NULL;

	int h_size = 1024;
	int a_size = 5;

	hHeap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_GENERATE_EXCEPTIONS,
		h_size, 0);
	
	if (!hHeap)
	{
		cout << "Heap create failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	a = (int*)HeapAlloc(hHeap, NULL, a_size * sizeof(int));
	
	for (int i = 0; i < a_size; i++)
	{
		a[i] = i;
		cout << "a[" << i << "] = " << a[i] << endl;
	}
	
	a = (int*)HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, a,
		2 * a_size * sizeof(int));
	
	for (int i = 0; i < 2 * a_size; i++)
		cout << "\ta[" << i << "] = " << a[i] << endl;
	
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