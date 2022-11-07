#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	const int size = 4096;

	HANDLE hProcess;
	SIZE_T min, max;
	SIZE_T* pMin = &min;
	SIZE_T* pMax = &max;
	
	hProcess = GetCurrentProcess();
	
	if (!GetProcessWorkingSetSize(hProcess, pMin, pMax))
	{
		cout << "Get process working set size failed." << endl;
		return GetLastError();
	}
	else
	{
		cout << "Min = " << (min / size) << endl;
		cout << "Max = " << (max / size) << endl;
	}
	
	if (!SetProcessWorkingSetSize(hProcess, min - 10, max - 10))
	{
		cout << "Set process working set size failed." << endl;
		return GetLastError();
	}
	
	if (!GetProcessWorkingSetSize(hProcess, pMin, pMax))
	{
		cout << "Get process working set size failed." << endl;
		return GetLastError();
	}
	else
	{
		cout << "Min = " << (min / size) << endl;
		cout << "Max = " << (max / size) << endl;
	}

	system("pause");

	return 0;
}