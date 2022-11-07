#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	int* p = NULL;
	__try
	{
		cout << "a = " << *p << endl;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cout << "There was some exception." << endl;
		p = &a;
	}
	cout << "a = " << *p << endl;

	system("pause");

	return 0;
}