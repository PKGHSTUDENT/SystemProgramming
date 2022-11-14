#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char file_name[] = "D:\\Demo.bin";
	char mapping_name[] = "MappingName";
	HANDLE hFile, hMapping; 
	int* ptr; 
	
	ofstream out(file_name, ios::out | ios::binary);
	if (!out)
	{
		cerr << "File constructor failed." << endl;
		return 0;
	}
	
	cout << "Initial array: ";
	for (int i = 0; i < 10; ++i)
	{
		out.write((char*)&a[i], sizeof(int));
		cout << a[i] << ' ';
	}
	cout << endl;
	
	out.close();
	
	hFile = CreateFile(file_name, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Create file failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	hMapping = CreateFileMapping(
		hFile, 
		NULL, 
		PAGE_READWRITE, 
		0, 0, 
		mapping_name);

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
	
	for (int i = 0; i < 10; ++i)
		ptr[i] += 10;
	
	if (!FlushViewOfFile(ptr, 0))
	{
		cerr << "Flush view of file failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	
	
	char lpszAppName[] = "D:\\Listing 30.5.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
	{
		cerr << "Create process failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	WaitForSingleObject(piApp.hProcess, INFINITE);
	
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	
	
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
	
	if (!CloseHandle(hFile))
	{
		cerr << "Close file failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	system("pause");

	return 0;
}