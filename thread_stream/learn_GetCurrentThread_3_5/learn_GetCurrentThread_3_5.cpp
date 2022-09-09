// Изучение функции GetCurrentThread.
//

#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HANDLE hThread;

	hThread = GetCurrentThread();

	cout << hThread << endl;

	cin.get();

	return 0;
}
