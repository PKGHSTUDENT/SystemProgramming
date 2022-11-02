#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HANDLE hThread;

	hThread = GetCurrentThread();

	cout << hThread << endl;

	system("pause");
	return 0;
}
