#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* p = NULL;

	__try
	{
		if (!p)
		{
			cout << "Exit with __leave from the try block." << endl;
			__leave;
		}
		else
		{
			*p = 10;
			cout << "*p = " << *p << endl;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cout << "There was some exception." << endl;
	}

	system("pause");

	return 0;
}