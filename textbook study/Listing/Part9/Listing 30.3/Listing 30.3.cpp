#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	char MappingName[] = "MappingName";
	HANDLE hMapping; 
	int* ptr; 
	const int n = 10; 
	cout << "This is a child process." << endl;
	
	hMapping = CreateFileMapping(
		INVALID_HANDLE_VALUE, 
		NULL, 
		PAGE_READWRITE, 
		0, 
		n * sizeof(int), 
		MappingName);

	if (!hMapping)
	{
		cerr << "Create file mapping failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	ptr = (int*)MapViewOfFile(
		hMapping, 
		FILE_MAP_WRITE, 
		0, 0, 
		0); 
	
	cout << "Array: ";
	
	for (int i = 0; i < n; ++i)
		cout << ptr[i] << ' ';
	cout << endl;
	
	if (!UnmapViewOfFile(ptr))
	{
		cerr << "Unmap view of file failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	if (!CloseHandle(hMapping))
	{
		cerr << "Close file failed." << endl;
		system("pause");
		return GetLastError();
	}

	system("pause");

	return 0;
}