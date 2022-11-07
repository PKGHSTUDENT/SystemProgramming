#include <windows.h>
#include <iostream>

#pragma warning(disable : 4703)

using namespace std;

int main()
{
	__try
	{
		int* a, * b;

		__try
		{
			a = new int(10);
			__try
			{
				b = new int(0);

				cout << "a/b = " << (*a) / (*b) << endl;
			}
			__finally
			{
				delete b;

				cout << "The memory for 'b' is free." << endl;
			}
		}
		__finally
		{
			delete a;

			cout << "The memory for 'a' is free." << endl;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cout << "There was some exception." << endl;
	}

	system("pause");

	return 0;
}