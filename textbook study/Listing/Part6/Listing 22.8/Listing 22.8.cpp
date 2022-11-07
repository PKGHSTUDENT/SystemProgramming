#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hHeap;
	
	int size = 1024;
	int* a = NULL, * b = NULL;
	
	PROCESS_HEAP_ENTRY phe;
	
	hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, 0);
	
	a = (int*)HeapAlloc(hHeap, NULL, 4 * sizeof(int));
	b = (int*)HeapAlloc(hHeap, NULL, 16 * sizeof(int));
	
	phe.lpData = NULL;
	
	while (HeapWalk(hHeap, &phe));
	{
		if (phe.wFlags & PROCESS_HEAP_REGION)
			cout << "PROCESS_HEAP_REGION flag is set." << endl;
		if (phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE)
			cout << "PROCESS_HEAP_UNCOMMITTED_RANGE flag is set" << endl;
		cout << "lpData = " << phe.lpData << endl;
		cout << "cbData = " << phe.cbData << endl;
		cout << endl;
	}
	
	HeapDestroy(hHeap);
	
	system("pause");
	
	return 0;
}