#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HMODULE hDll;
	int (*Add)(int);
	int (*Sub)(int);
	int* pCount;

	hDll = LoadLibrary("D:\\ListingDLL 31.4.dll");
	
	if (!hDll)
	{
		cerr << "Load library failed." << endl;
		system("pause");
		return GetLastError();
	}
	
	pCount = (int*)GetProcAddress(hDll, MAKEINTRESOURCE(1));
	
	if (!pCount)
	{
		cerr << "Get variable address failed." << endl;
		system("pause");
		return GetLastError();
	}

	cout << "Initial count = " << (*pCount) << endl;
	
	Add = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(2));
	Sub = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(3));
	
	if (!Add || !Sub)
	{
		cerr << "Get procedure address failed." << endl;
		system("pause");
		return GetLastError();
	}

	cout << "count = " << Add(20) << endl;
	cout << "count = " << Sub(15) << endl;

	if (!FreeLibrary(hDll))
	{
		cerr << "Free library failed." << endl;
		system("pause");
		return GetLastError();
	}

	system("pause");
	
	return 0;
}