#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hHeap;

	int* a = NULL;
	
	// int size = 4096;
	int size = 1024;
	
	hHeap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_GENERATE_EXCEPTIONS,
		size, size);

	if (!hHeap)
	{
		cout << "Heap create failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	__try
	{
		a = (int*)HeapAlloc(hHeap, NULL, size * sizeof(int));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD ecode = GetExceptionCode();
	
		if (ecode == STATUS_NO_MEMORY)
			cout << "STATUS_NO_MEMORY exception." << endl;
		else
			cout << "Some exception." << endl;
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